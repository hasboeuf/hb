/****************************************************************************
** Copyright (C) 2012-2015 Adrien Gavignet (hasboeuf)
** Contact: adrien.gavignet@gmail.com
**
** This file is part of the Hb module. Provided "AS IS", WITHOUT WARRANTIES
** OR CONDITIONS OF ANY KIND, either express or implied.
****************************************************************************/

#ifndef HBNETWORKUSER_H
#define HBNETWORKUSER_H

/*! \file HbNetworkUser.h */

// Qt
#include <QtCore/QObject>
#include <QtCore/QSet>
// Hb
// Local
#include <HbNetwork.h>
#include <user/HbNetworkUserData.h>
#include <contract/HbNetworkProtocol.h>

namespace hb
{
    namespace network
    {
        /*!
         * TODOC
         */
        class HB_NETWORK_DECL HbNetworkUser : public QObject
        {
            Q_OBJECT
        public:

            HbNetworkUser();
            virtual ~HbNetworkUser( ) = default;

            void reset(); // Used on client side.

            ShConstHbNetworkUserInfo & info();
            void setInfo( const HbNetworkUserInfo & info );

            HbNetworkProtocol::UserStatus status() const;
            void setStatus( HbNetworkProtocol::UserStatus status );

            networkuid mainSocketUid() const;
            void setMainSocketUid( networkuid socket_uid );

            const QSet< networkuid > & socketsUid() const;

            const HbNetworkUserData createData( networkuid socket_id );
        signals:
            void statusChanged( HbNetworkProtocol::UserStatus status );

        private:
            ShConstHbNetworkUserInfo mInfo;
            HbNetworkProtocol::UserStatus mStatus;
            networkuid mMainSocketUid;
            QSet< networkuid > mSocketsUid;
        };
    }
}

#endif // HBNETWORKUSER_H
