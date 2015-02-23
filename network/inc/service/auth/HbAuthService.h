/****************************************************************************
** Copyright (C) 2012-2015 Adrien Gavignet (hasboeuf)
** Contact: adrien.gavignet@gmail.com
**
** This file is part of the Hb module. Provided "AS IS", WITHOUT WARRANTIES
** OR CONDITIONS OF ANY KIND, either express or implied.
****************************************************************************/

#ifndef HBAUTHSERVICE_H
#define HBAUTHSERVICE_H

// Qt
// Hb
// Local
#include <service/HbNetworkService.h>
#include <user/HbNetworkUserInfo.h>
#include <listener/IHbSocketListener.h>

namespace hb
{
    namespace network
    {

        class HB_NETWORK_DECL HbAuthService : public HbNetworkService, public IHbSocketListener
        {
            Q_OBJECT
        public:
            enum AuthType : authstgy
            {
                AUTH_NONE = 0,
                AUTH_FACEBOOK,
                AUTH_USER = 255
            };

            HbAuthService();
            virtual ~HbAuthService() = default;
            virtual HbNetworkProtocol::NetworkTypes enabledNetworkTypes() const;
            virtual void plugContracts( HbNetworkExchanges & exchanges );

        signals:
            void userAuthenticated  ( networkuid socket_uid, const HbNetworkUserInfo & user_info );
            void userUnauthenticated( networkuid socket_uid, const QString reason = QString() );

        public callbacks:
            virtual void onContractReceived( const HbNetworkContract * contract ) = 0;
            virtual void onSocketConnected   ( networkuid socket_uid ) = 0;
            virtual void onSocketDisconnected( networkuid socket_uid ) = 0;

        protected:
            QSet< networkuid > mPendingSocket;
        };
    }
}

#endif // HBAUTHSERVICE_H
