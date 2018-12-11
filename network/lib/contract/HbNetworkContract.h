/****************************************************************************
** Copyright (C) 2012-2015 Adrien Gavignet (hasboeuf)
** Contact: adrien.gavignet@gmail.com
**
** This file is part of the Hb module. Provided "AS IS", WITHOUT WARRANTIES
** OR CONDITIONS OF ANY KIND, either express or implied.
****************************************************************************/

#ifndef HBNETWORKCONTRACT_H
#define HBNETWORKCONTRACT_H

/*! \file HbNetworkContract.h */

// Qt
#include <QtCore/QObject>
#include <QtCore/QSet>
#include <QtCore/QSharedPointer>
#include <QtCore/QStringList>
// Hb
#include <HbGlobal.h>
// Local
#include <HbNetwork.h>
#include <contract/HbNetworkHeader.h>
#include <contract/HbNetworkProtocol.h>
#include <user/HbNetworkUserInfo.h>

namespace hb {
namespace network {
/*!
 * TODOC
 */
class HB_NETWORK_DECL HbNetworkContract {
    friend class HbNetworkExchanges;

public:
    virtual ~HbNetworkContract();

    virtual bool isValid() const;

    virtual void setHeader(const HbNetworkHeader& header);
    virtual const HbNetworkHeader& header() const;

    virtual void setSender(networkuid sender);
    virtual networkuid sender() const;

    virtual void addPendingReceiver(ShConstHbNetworkUserInfo users_infos);
    virtual void addSocketReceiver(networkuid socket_uid);
    virtual const QList<ShConstHbNetworkUserInfo>& pendingReceivers() const;
    virtual const QSet<networkuid>& receivers() const;
    virtual networkuid receiver() const;

    virtual void setNetworkReceiver(networkuid network_receiver);
    virtual networkuid networkReceiver() const;

    virtual HbNetworkProtocol::RoutingScheme routing() const;
    virtual bool setRouting(HbNetworkProtocol::RoutingScheme routing);

    virtual HbNetworkContract* takeReply() const;
    virtual void updateReply();

    virtual QString toString() const;

    virtual void setNetworkType(HbNetworkProtocol::NetworkType type);
    virtual HbNetworkProtocol::NetworkType networkType() const;

    template <typename T> inline const T* value() const {
        return dynamic_cast<const T*>(this);
    }

    template <typename T> inline T* value() {
        return dynamic_cast<T*>(this);
    }

    virtual bool read(QDataStream& stream) = 0;
    virtual bool write(QDataStream& stream) const = 0;

protected:
    HbNetworkContract();
    HbNetworkContract(serviceuid service, codeuid code);
    HbNetworkContract(const HbNetworkContract& source);
    HbNetworkContract& operator=(const HbNetworkContract& source);

    virtual HbNetworkContract* create() const = 0;

    HbNetworkHeader mHeader;
    HbNetworkContract* mpReply;

private:
    void resetReceivers();

    //! \todo Internal use. Server side. Protect the client side.
    networkuid mSender;
    HbNetworkProtocol::NetworkType mNetworkType;
    HbNetworkProtocol::RoutingScheme mRouting;

    QList<ShConstHbNetworkUserInfo> mPendingReceivers; // Users infos, morph into networkuid at sending time.
    QSet<networkuid> mReceivers;

    networkuid mNetworkReceiver; // Used by server channels.
};

typedef QSharedPointer<const HbNetworkContract> ShConstHbNetworkContract;
typedef QSharedPointer<HbNetworkContract> ShHbNetworkContract;
} // namespace network
} // namespace hb

using hb::network::HbNetworkContract;

#endif // HBNETWORKCONTRACT_H
