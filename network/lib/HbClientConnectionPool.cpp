// Qt
// Hb
#include <HbGlobal.h>
#include <HbLogService.h>
#include <facebook/HbO2ClientFacebook.h>
// Local
#include <HbClientConnectionPool.h>
#include <com/tcp/HbTcpClient.h>
#include <contract/general/HbKickContract.h>
#include <listener/IHbSocketListener.h>
#include <listener/IHbUserListener.h>
#include <service/auth/HbClientAuthFacebookStrategy.h>
#include <service/auth/HbClientAuthGoogleStrategy.h>
#include <service/auth/HbClientAuthLoginObject.h>
#include <service/auth/HbClientAuthService.h>
#include <service/channel/HbClientChannelService.h>
#include <service/presence/HbClientPresenceService.h>
#include <user/HbNetworkUser.h>

using namespace hb::network;

HbClientConnectionPool::HbClientConnectionPool(const HbGeneralClientConfig& config) : HbConnectionPool(config) {
    HbClientPresenceService* service_presence = new HbClientPresenceService();
    HbClientAuthService* service_auth = new HbClientAuthService();
    HbClientChannelService* service_channel = new HbClientChannelService();

    service_presence->setConfig(config.presence());
    service_auth->setConfig(config.auth());
    service_channel->setConfig(config.channel());

    // Facebook auth
    if (config.auth().facebookAuthConfig().isValid()) {
        HbClientAuthFacebookStrategy* fb_strategy = new HbClientAuthFacebookStrategy();
        fb_strategy->setConfig(config.auth().facebookAuthConfig());
        service_auth->addStrategy(fb_strategy);
    }

    // Google auth
    if (config.auth().googleAuthConfig().isValid()) {
        HbClientAuthGoogleStrategy* gl_strategy = new HbClientAuthGoogleStrategy();
        gl_strategy->setConfig(config.auth().googleAuthConfig());
        service_auth->addStrategy(gl_strategy);
    }

    mServices.insert(service_presence->uid(), service_presence);
    mServices.insert(service_auth->uid(), service_auth);
    mServices.insert(service_channel->uid(), service_channel);

    connect(service_auth,
            &HbAuthService::socketAuthenticated,
            this,
            &HbClientConnectionPool::onSocketAuthenticated,
            Qt::UniqueConnection);
    connect(service_auth,
            &HbAuthService::socketUnauthenticated,
            this,
            &HbClientConnectionPool::onSocketUnauthenticated,
            Qt::UniqueConnection);

    for (HbNetworkService* service : mServices) {
        q_assert_ptr(service);

        // From services.
        connect(service, &HbNetworkService::contractToSend, this, &HbClientConnectionPool::onContractToSend);

        // To services.
        // Contract listener.
        IHbContractListener* contract_listener = dynamic_cast<IHbContractListener*>(service);
        if (contract_listener) {
            connect(this,
                    &HbConnectionPool::socketContractReceived,
                    [contract_listener](const HbNetworkContract* contract) {
                        contract_listener->onContractReceived(contract);
                    });
        }

        // Socket.
        IHbSocketListener* socket_listener = dynamic_cast<IHbSocketListener*>(service);
        if (socket_listener) {
            connect(this, &HbConnectionPool::socketConnected, [socket_listener](networkuid socket_uid) {
                socket_listener->onSocketConnected(socket_uid);
            });
            connect(this, &HbConnectionPool::socketDisconnected, [socket_listener](networkuid socket_uid) {
                socket_listener->onSocketDisconnected(socket_uid);
            });
        }

        // Socket auth.
        IHbSocketAuthListener* socket_auth_listener = dynamic_cast<IHbSocketAuthListener*>(service);
        if (socket_auth_listener) {
            connect(this, &HbConnectionPool::socketAuthenticated, [socket_auth_listener](networkuid socket_uid) {
                socket_auth_listener->onSocketAuthenticated(socket_uid);
            });
            connect(this, &HbConnectionPool::socketUnauthenticated, [socket_auth_listener](networkuid socket_uid) {
                socket_auth_listener->onSocketUnauthenticated(socket_uid);
            });
        }

        // User.
        IHbUserListener* user_listener = dynamic_cast<IHbUserListener*>(service);
        if (user_listener) {
            connect(this, &HbConnectionPool::userConnected, [user_listener](ShConstHbNetworkUserInfo user_info) {
                user_listener->onUserConnected(user_info);
            });
            connect(this, &HbConnectionPool::userDisconnected, [user_listener](ShConstHbNetworkUserInfo user_info) {
                user_listener->onUserDisconnected(user_info);
            });
        }

        // User contract listener.
        IHbClientUserContractListener* user_contract_listener = dynamic_cast<IHbClientUserContractListener*>(service);
        if (user_contract_listener) {
            connect(
                this,
                &HbConnectionPool::userContractReceived,
                [user_contract_listener](ShConstHbNetworkUserInfo /*user_info*/, const HbNetworkContract* contract) {
                    user_contract_listener->onUserContractReceived(contract);
                });
        }
    }

    connect(&mUser, &HbClientUser::statusChanged, this, &HbClientConnectionPool::onMeStatusChanged);
}

HbClientConnectionPool::~HbClientConnectionPool() {
    leave();
}

networkuid HbClientConnectionPool::joinTcpClient(HbTcpClientConfig& config, bool main) {
    networkuid network_uid = 0;
    if (mUser.mainSocketUid() > 0) {
        qWarning() << "Impossible to create two main clients";
        return network_uid;
    }

    HbTcpClient* client = new HbTcpClient();

    setExchanges(config.exchanges());

    config.setBadHeaderTolerant(false); // Force header checking.
    client->setConfiguration(config);

    connect(client,
            &HbAbstractClient::clientConnected,
            this,
            &HbClientConnectionPool::onClientConnected,
            Qt::UniqueConnection);
    connect(client,
            &HbAbstractClient::clientDisconnected,
            this,
            &HbClientConnectionPool::onClientDisconnected,
            Qt::UniqueConnection);

    if (!client->join()) {
        delete client;
        return 0;
    }

    network_uid = client->uid();

    for (HbNetworkChannel* channel : config.channels()) {
        plugChannel(channel, network_uid);
    }

    mClients.insert(network_uid, client);

    mUser.addSocket(network_uid, main);

    return network_uid;
}

bool HbClientConnectionPool::leave() {
    mLeaving = true;

    // Reset
    mUser.reset();
    HbConnectionPool::reset(); // Reset services before deleting clients.

    QHash<networkuid, HbAbstractClient*> copy = mClients;
    // Local copy as onClientDisconnected remove items of mClients bit by bit.
    qDeleteAll(copy);

    // onClientDisconnected is called there and handles:
    // - mClients

    mLeaving = false;

    q_assert(mClients.isEmpty());

    return true;
}

bool HbClientConnectionPool::authRequested(HbClientAuthLoginObject* login_object) {
    if (!login_object) {
        qWarning() << "Login object null";
        return false;
    }

    if (mUser.status() != HbNetworkProtocol::USER_CONNECTED) {
        qWarning() << "User not in a connected state";
        return false;
    }

    HbClientAuthService* auth_service = getService<HbClientAuthService>(HbNetworkProtocol::SERVICE_AUTH);
    q_assert_ptr(auth_service);

    login_object->setSocketUid(mUser.mainSocketUid());
    mUser.setStatus(HbNetworkProtocol::USER_AUTHENTICATING);

    auth_service->onAuthRequested(login_object);

    return false;
}

void HbClientConnectionPool::onClientConnected(networkuid client_uid) {
    HbAbstractClient* client = dynamic_cast<HbAbstractClient*>(sender());
    q_assert_ptr(client);
    q_assert(mClients.contains(client_uid));

    connect(client,
            &HbAbstractClient::clientContractReceived,
            this,
            &HbClientConnectionPool::onClientContractReceived,
            Qt::UniqueConnection);

    qDebug() << "Client" << client_uid << "connected";

    emit statusChanged(client_uid, HbNetworkProtocol::CLIENT_CONNECTED);

    if (client_uid == mUser.mainSocketUid()) {
        mUser.setStatus(HbNetworkProtocol::USER_CONNECTED);
    }
}

void HbClientConnectionPool::onClientDisconnected(networkuid client_uid) {
    HbAbstractClient* client = dynamic_cast<HbAbstractClient*>(sender());
    q_assert_ptr(client);
    q_assert(mClients.contains(client_uid));

    if (mUser.status() > HbNetworkProtocol::USER_CONNECTED) {
        emit socketUnauthenticated(client_uid);
    }

    emit statusChanged(client_uid, HbNetworkProtocol::CLIENT_DISCONNECTED);
    emit socketDisconnected(client_uid); // To IHbSocketListener.

    bool reconnecting = (client->configuration().reconnectionDelay() > 0 ? true : false);
    if (mLeaving) // If HbClient is leaving.
    {
        qDebug() << "HbClient is leaving. Client" << client_uid << "removed";
        mClients.remove(client_uid);

        // Deletion is handled in leave()
        // Unplugging channels is done in leave().
        // User reset is done in leave().
    } else {
        qDebug() << "Client" << client_uid << "disconnected";
        if (!reconnecting) {
            qDebug() << "Client" << client_uid << "will not reconnect, deletion...";

            // Unplug channels.
            for (HbNetworkChannel* channel : client->configuration().channels()) {
                q_assert_ptr(channel);
                HbConnectionPool::unplugChannel(channel);
            }

            mClients.remove(client_uid);
            client->deleteLater();

            if (client_uid == mUser.mainSocketUid()) {
                qDebug() << "Client" << client_uid << "was the main client, reset";
                mUser.reset();
            }
        } else {
            // It will reconnect so we do not unplug channels but we reset it.
            for (HbNetworkChannel* channel : client->configuration().channels()) {
                q_assert_ptr(channel);
                channel->internalReset(/*keep_uid*/ true);
                channel->reset();
            }

            if (client_uid == mUser.mainSocketUid()) {
                mUser.reset();
                mUser.addSocket(client_uid, true); // Keep the main socket as it will reconnect. // TODO
            }
        }
    }
}

void HbClientConnectionPool::onClientContractReceived(networkuid client_uid, const HbNetworkContract* contract) {
    HbAbstractClient* client = dynamic_cast<HbAbstractClient*>(sender());
    q_assert_ptr(client);
    q_assert(mClients.contains(client_uid));

    qDebug() << "Contract received from client" << client_uid;

    serviceuid requested_service = contract->header().service();

    qDebug() << QString("Contract OK [client=%1, %2]").arg(client_uid).arg(contract->header().toString());

    if (checkKickReceived(contract)) {
        delete contract;
        return;
    }

    bool is_authenticated = true;
    if (mUser.status() != HbNetworkProtocol::USER_AUTHENTICATED) {
        is_authenticated = false;
        q_assert(requested_service == HbNetworkProtocol::SERVICE_AUTH);
    }

    HbNetworkService* service = getService(requested_service);
    if (!service) {
        qWarning() << "Service" << HbNetworkProtocol::MetaService::toString(contract->header().service())
                   << "is not instanciated";
        return;
    }

    if (is_authenticated) {
        IHbClientUserContractListener* auth_service = dynamic_cast<IHbClientUserContractListener*>(service);
        q_assert_ptr(auth_service);
        auth_service->onUserContractReceived(contract);
    } else {
        IHbContractListener* unauth_service = dynamic_cast<IHbContractListener*>(service);
        q_assert_ptr(unauth_service);
        unauth_service->onContractReceived(contract);
    }
}

void HbClientConnectionPool::onContractToSend(const HbNetworkContract* contract) {
    ShConstHbNetworkContract shared_contract(contract);
    if (contract->isValid()) {
        auto receivers = contract->receivers();
        for (networkuid receiver : receivers) {
            HbAbstractClient* client = mClients.value(receiver, nullptr);
            if (client) {
                client->send(shared_contract);
            } else {
                qWarning() << "Receiver" << receiver << "does not exist";
            }
        }
    } else {
        qWarning() << "Try to send an invalid contract";
    }
}

void HbClientConnectionPool::onSocketAuthenticated(networkuid socket_uid, const HbNetworkUserInfo& user_info) {
    q_assert(socket_uid > 0);

    if (mUser.mainSocketUid() == socket_uid) {
        mUser.setInfo(user_info);
        mUser.setStatus(HbNetworkProtocol::USER_AUTHENTICATED);
        qDebug() << "User" << user_info.email() << "is authenticated";
    }

    qDebug() << "Socket" << socket_uid << "authenticated";

    emit socketAuthenticated(socket_uid); // To IHbSocketAuthListener.
}

void HbClientConnectionPool::onSocketUnauthenticated(networkuid socket_uid,
                                                     quint8 try_number,
                                                     quint8 max_tries,
                                                     const QString& reason) {
    q_assert(socket_uid > 0);

    if (mUser.mainSocketUid() == socket_uid) {
        mUser.setInfo(HbNetworkUserInfo());
        mUser.setStatus(HbNetworkProtocol::USER_CONNECTED);
        qDebug() << "User (me) is unauthenticated";
    }

    qDebug() << QString("Socket %1 unauthenticated (try_number=%2, max_tries=%3, reason=%4)")
                    .arg(socket_uid)
                    .arg(try_number)
                    .arg(max_tries)
                    .arg(reason);

    //! \todo Send reason to HbClient.

    emit socketUnauthenticated(socket_uid); // To IHbSocketAuthListener.
}

void HbClientConnectionPool::onMeStatusChanged(HbNetworkProtocol::UserStatus status) {
    emit meStatusChanged(status, mUser.info());
}

bool HbClientConnectionPool::checkKickReceived(const HbNetworkContract* contract) {
    q_assert_ptr(contract);

    if (contract->header().service() == HbNetworkProtocol::SERVICE_KICK
        && contract->header().code() == HbNetworkProtocol::CODE_SRV_KICK) {
        const HbKickContract* kick_contract = contract->value<HbKickContract>();
        q_assert_ptr(kick_contract);

        qWarning() << QString("Kick contract received! (reason=%1, description=%2)")
                          .arg(HbNetworkProtocol::MetaKickCode::toString(kick_contract->reason()))
                          .arg(kick_contract->description());

        //! \todo Tell it to HbClient.

        return true;
    }

    return false;
}
