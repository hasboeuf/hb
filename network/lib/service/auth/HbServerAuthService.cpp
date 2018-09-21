// Qt
// Hb
#include <HbLogService.h>
// Local
#include <contract/auth/HbAuthRequestContract.h>
#include <contract/auth/HbAuthStatusContract.h>
#include <contract/auth/HbOAuthRequestContract.h>
#include <service/auth/HbServerAuthFacebookStrategy.h>
#include <service/auth/HbServerAuthService.h>
#include <service/auth/HbServerAuthStrategy.h>

using namespace hb::network;

HbServerAuthService::HbServerAuthService() {
    mTimerId = 0;
}

HbServerAuthService::~HbServerAuthService() {
    qDeleteAll(mStrategies);
}

void HbServerAuthService::reset() {
    for (HbServerAuthStrategy* strategy : mStrategies) {
        strategy->reset();
    }

    for (networkuid socket_uid : mPendingSocket) {
        delSocket(socket_uid);
    }
}

const HbServiceAuthServerConfig& HbServerAuthService::config() const {
    return mConfig;
}

void HbServerAuthService::setConfig(const HbServiceAuthServerConfig& config) {
    if (config.isValid()) {
        mConfig = config;
    }
}

void HbServerAuthService::addStrategy(HbServerAuthStrategy* strategy) {
    if (strategy && !mStrategies.contains(strategy->type())) {
        mStrategies.insert(strategy->type(), strategy);

        connect(strategy,
                &HbServerAuthStrategy::authFailed,
                this,
                &HbServerAuthService::onAuthFailed,
                Qt::UniqueConnection);
        connect(strategy,
                &HbServerAuthStrategy::authSucceed,
                this,
                &HbServerAuthService::onAuthSucceed,
                Qt::UniqueConnection);
    } else {
        qWarning() << "Strategy already defined or null";
    }
}

void HbServerAuthService::timerEvent(QTimerEvent*) {
    auto it = mAuthTimeout.begin();
    while (it != mAuthTimeout.end()) {
        auto current = it++;

        networkuid socket_uid = current.key();
        quint8 timeout = current.value();

        if (timeout > mConfig.authTimeout()) {
            delSocket(socket_uid);
            emit socketToKick(socket_uid,
                              HbNetworkProtocol::KICK_AUTH_TIMEOUT,
                              QString("Reach %1 seconds auth timeout.").arg(timeout));

            //! \todo Check deletion.
        } else {
            mAuthTimeout[socket_uid]++; // Increment one second.
        }
    }
}

bool HbServerAuthService::checkSocket(networkuid socket_uid) {
    quint8 flags = 0x0;
    if (mPendingSocket.contains(socket_uid))
        flags |= 0x1;
    if (mAuthTimeout.contains(socket_uid))
        flags |= 0x2;
    if (mAuthTries.contains(socket_uid))
        flags |= 0x4;

    if (flags == 0x7) // All contains socket_uid.
    {
        return true;
    } else if (flags != 0x0) // Something incoherent is here, socket_uid is not present everywhere.
    {
        kickSocket(socket_uid, HbNetworkProtocol::KICK_INTERNAL_ERROR);
    }

    return false;
}

void HbServerAuthService::addSocket(networkuid socket_uid) {
    if (mPendingSocket.isEmpty()) {
        mTimerId = startTimer(1000);
    }

    mPendingSocket.insert(socket_uid);
    mAuthTimeout.insert(socket_uid, 0); // Init 0 sec.
    mAuthTries.insert(socket_uid, 0);
}

void HbServerAuthService::delSocket(networkuid socket_uid, bool delete_responses) {
    mPendingSocket.remove(socket_uid);
    mAuthTries.remove(socket_uid);
    mAuthTimeout.remove(socket_uid);

    if (mPendingSocket.isEmpty() && mTimerId) {
        killTimer(mTimerId);
        mTimerId = 0;
    }

    HbNetworkContract* response = mResponses.value(socket_uid, nullptr);
    if (response) {
        mResponses.remove(socket_uid);
        if (delete_responses) {
            delete response;
        } else {
            // Response is now being sent, deletion is handled in sending mechanism.
        }
    }
}

void HbServerAuthService::kickSocket(networkuid socket_uid,
                                     HbNetworkProtocol::KickCode reason,
                                     const QString& description) {
    delSocket(socket_uid);
    emit socketToKick(socket_uid, reason, description);
}

void HbServerAuthService::onContractReceived(const HbNetworkContract* contract) {
    q_assert_ptr(contract);

    const HbAuthRequestContract* auth_contract = contract->value<HbAuthRequestContract>();
    if (auth_contract) {
        authstgy type = auth_contract->type();
        networkuid socket_uid = auth_contract->sender();

        HbServerAuthStrategy* strategy = mStrategies.value(type, nullptr);
        if (strategy) {
            HbAuthStatusContract* response = auth_contract->takeReply();
            if (response && response->receiver() == socket_uid) {
                mResponses.insert(socket_uid, response);

                if (strategy->checkLogin(auth_contract)) {
                    q_assert(mAuthTries.contains(socket_uid));
                    mAuthTries[socket_uid]++;
                } else {
                    qWarning() << "Bad contract";
                    kickSocket(socket_uid, HbNetworkProtocol::KICK_CONTRACT_INVALID, "Bad contract.");
                }
            } else {
                qWarning() << "Bad reply contract";
                kickSocket(socket_uid, HbNetworkProtocol::KICK_CONTRACT_INVALID, "Bad reply contract.");
            }
        } else {
            qWarning() << "No user auth strategy defined";
            kickSocket(socket_uid, HbNetworkProtocol::KICK_CONTRACT_INVALID, "No user auth strategy defined.");
        }

    } else {
        qWarning() << "Auth contract type not recognized";
        //! \todo How to kick?
    }

    delete contract;
}

void HbServerAuthService::onSocketConnected(networkuid socket_uid) {
    addSocket(socket_uid);
}

void HbServerAuthService::onSocketDisconnected(networkuid socket_uid) {
    delSocket(socket_uid);
}

void HbServerAuthService::onAuthSucceed(networkuid socket_uid, const HbNetworkUserInfo& user_info) {
    HbNetworkUserInfo i = user_info;

    if (checkSocket(socket_uid)) {
        HbAuthStatusContract* response = mResponses.value(socket_uid, nullptr);
        if (!response) {
            kickSocket(socket_uid, HbNetworkProtocol::KICK_INTERNAL_ERROR);
            return;
        }

        response->setStatus(HbNetworkProtocol::AUTH_OK);
        response->setTryNumber(mAuthTries[socket_uid]);
        response->setMaxTries(mConfig.authMaxTries());
        response->setUserInfo(user_info);

        delSocket(socket_uid, false);

        emit contractToSend(response);

        // Should be called after sending client's ack otherwise client will receive a channel contract
        // (HbUserSyncContract) before being authenticated (from its point of view).
        emit socketAuthenticated(socket_uid, user_info);
    } else {
        qWarning() << "Socket" << socket_uid << "disconnected before getting ok auth response";
    }
}

void HbServerAuthService::onAuthFailed(networkuid socket_uid,
                                       HbNetworkProtocol::AuthStatus status,
                                       const QString& description) {
    if (checkSocket(socket_uid)) {
        HbAuthStatusContract* response = mResponses.value(socket_uid, nullptr);
        if (!response) {
            kickSocket(socket_uid, HbNetworkProtocol::KICK_INTERNAL_ERROR);
            return;
        }

        q_assert(mAuthTries.contains(socket_uid));

        response->setStatus(status);
        response->setDescription(description);
        response->setTryNumber(mAuthTries[socket_uid]);
        response->setMaxTries(mConfig.authMaxTries());

        emit contractToSend(response);

        if (mAuthTries[socket_uid] == mConfig.authMaxTries()) {
            kickSocket(socket_uid, HbNetworkProtocol::KICK_AUTH_LIMIT);
        }
    } else {
        qWarning() << "Socket" << socket_uid << "disconnected before getting nok auth response";
    }
}
