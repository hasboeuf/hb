/****************************************************************************
** Copyright (C) 2012-2015 Adrien Gavignet (hasboeuf)
** Contact: adrien.gavignet@gmail.com
**
** This file is part of the Hb module. Provided "AS IS", WITHOUT WARRANTIES
** OR CONDITIONS OF ANY KIND, either express or implied.
****************************************************************************/

#ifndef HBCLIENTAUTHSERVICE_H
#define HBCLIENTAUTHSERVICE_H

/*! \file HbClientAuthService.h */

// Qt
// Hb
// Local
#include <service/auth/HbAuthService.h>
#include <config/service/auth/HbServiceAuthClientConfig.h>

namespace hb
{
    namespace link
    {
        class HbO2ClientFacebook;
    }
    namespace network
    {
        class HbClientAuthStrategy;
        class HbClientAuthLoginObject;
        class HbAuthRequestContract;

        /*!
         * TODOC
         */
        class HB_NETWORK_DECL HbClientAuthService : public HbAuthService
        {
            Q_OBJECT

        public:

            HbClientAuthService();
            virtual ~HbClientAuthService() = default;

            virtual void reset();
            const HbServiceAuthClientConfig & config() const;
            void setConfig( const HbServiceAuthClientConfig & config );

            void addStrategy( HbClientAuthStrategy * strategy );

        public callbacks:
            virtual void onContractReceived( const HbNetworkContract * contract );
            virtual void onSocketConnected   ( networkuid socket_uid );
            virtual void onSocketDisconnected( networkuid socket_uid );

            // From ClientConnectionPool.
            void onAuthRequested( HbClientAuthLoginObject * login_object );

            // From HbClientAuthStrategy.
            void onAuthContractReady ( networkuid socket_uid, HbAuthRequestContract * contract );
            void onAuthContractFailed( networkuid socket_uid, const QString & description );

        private:
            networkuid mPendingSocket;
            HbServiceAuthClientConfig mConfig;
            QHash< authstgy, HbClientAuthStrategy * > mStrategies;

        };
    }
}

#endif // HBCLIENTAUTHSERVICE_H
