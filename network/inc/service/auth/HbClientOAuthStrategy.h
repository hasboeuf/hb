/****************************************************************************
** Copyright (C) 2012-2015 Adrien Gavignet (hasboeuf)
** Contact: adrien.gavignet@gmail.com
**
** This file is part of the Hb module. Provided "AS IS", WITHOUT WARRANTIES
** OR CONDITIONS OF ANY KIND, either express or implied.
****************************************************************************/

#ifndef HBCLIENTOAUTHSTRATEGY_H
#define HBCLIENTOAUTHSTRATEGY_H

// Qt
#include <QtCore/QHash>
// Hb
#include <HbO2Client.h>
// Local
#include <HbNetwork.h>
#include <service/auth/HbClientAuthStrategy.h>
#include <contract/HbNetworkProtocol.h>
#include <contract/auth/HbAuthRequestContract.h> // Template.

namespace hb
{
    using namespace link;

    namespace network
    {
        /*!
         * TODOC
         */
        class HB_NETWORK_DECL HbClientOAuthStrategy : public HbClientAuthStrategy
        {
            Q_OBJECT
        public:

            HbClientOAuthStrategy() = default;
            virtual ~HbClientOAuthStrategy();

            virtual void reset() override;

            virtual void setConfig( const HbO2ClientConfig & config );

        public slots:
            void onLinkSucceed();
            void onLinkFailed();

        protected:
            QHash< HbO2Client *, networkuid > mPendingCodes;
            HbO2ClientConfig mConfig;
        };
    }
}

using hb::network::HbClientOAuthStrategy;

#endif // HBCLIENTOAUTHSTRATEGY_H
