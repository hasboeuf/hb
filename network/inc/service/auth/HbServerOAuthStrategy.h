/****************************************************************************
** Copyright (C) 2012-2015 Adrien Gavignet (hasboeuf)
** Contact: adrien.gavignet@gmail.com
**
** This file is part of the Hb module. Provided "AS IS", WITHOUT WARRANTIES
** OR CONDITIONS OF ANY KIND, either express or implied.
****************************************************************************/

#ifndef HBSERVEROAUTHSTRATEGY_H
#define HBSERVEROAUTHSTRATEGY_H

// Qt
#include <QtCore/QHash>
// Hb
#include <config/HbO2ServerConfig.h>
// Local
#include <HbNetwork.h>
#include <service/auth/HbServerAuthStrategy.h>
#include <contract/HbNetworkProtocol.h>
#include <contract/auth/HbAuthRequestContract.h> // Template.

namespace hb
{
    namespace link
    {
        class HbO2Server;
    }

    using namespace link;

    namespace network
    {
        class HbAuthRequestContract;

        /*!
         * TODOC
         */
        class HB_NETWORK_DECL HbServerOAuthStrategy : public HbServerAuthStrategy
        {
            Q_OBJECT
        public:

            HbServerOAuthStrategy();
            virtual ~HbServerOAuthStrategy() = default;

            virtual void reset() override;

            virtual void setConfig( const HbO2ServerConfig & config );

        public slots:
            void onLinkFailed( const QString & error );

        protected:
            QHash< HbO2Server *, networkuid > mPendingToken;
            QHash< quint64, networkuid >      mPendingRequest;
            HbO2ServerConfig                  mConfig;
        };
    }
}

using hb::network::HbServerOAuthStrategy;

#endif // HBSERVEROAUTHSTRATEGY_H
