/****************************************************************************
** Copyright (C) 2012-2015 Adrien Gavignet (hasboeuf)
** Contact: adrien.gavignet@gmail.com
**
** This file is part of the Hb module. Provided "AS IS", WITHOUT WARRANTIES
** OR CONDITIONS OF ANY KIND, either express or implied.
****************************************************************************/

#ifndef HBNETWORKUSER_H
#define HBNETWORKUSER_H

// Qt
#include <QtCore/QObject>
// Hb
// Local
#include <HbNetwork.h>
#include <user/HbNetworkUserInfo.h>
#include <contract/HbNetworkProtocol.h>

namespace hb
{
    namespace network
    {
        class HB_NETWORK_DECL HbNetworkUser : public QObject
        {
            Q_OBJECT
        public:

            HbNetworkUser();
            virtual ~HbNetworkUser( ) = default;

            const HbNetworkUserInfo & info() const;
            void setInfo( const HbNetworkUserInfo & info );

            HbNetworkProtocol::UserStatus status() const;
            void setStatus( HbNetworkProtocol::UserStatus status );

            networkuid socketUid() const;
            void setSocketUid( networkuid socket_uid );

        signals:
            statusChanged( HbNetworkProtocol::UserStatus status );

        private:
            HbNetworkUserInfo mInfo;
            HbNetworkProtocol::UserStatus mStatus;
            networkuid mSocketUid;
        };
    }
}

#endif // HBNETWORKUSER_H
