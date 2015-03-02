/****************************************************************************
** Copyright (C) 2012-2015 Adrien Gavignet (hasboeuf)
** Contact: adrien.gavignet@gmail.com
**
** This file is part of the Hb module. Provided "AS IS", WITHOUT WARRANTIES
** OR CONDITIONS OF ANY KIND, either express or implied.
****************************************************************************/

#ifndef HBCLIENTAUTHFACEBOOKSTRATEGY_H
#define HBCLIENTAUTHFACEBOOKSTRATEGY_H

// Qt
#include <QtCore/QHash>
// Hb
#include <facebook/HbO2ClientFacebook.h>
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
        class HbAuthRequestContract;

        class HB_NETWORK_DECL HbClientAuthFacebookStrategy : public HbClientAuthStrategy
        {
            Q_OBJECT
        public:

            HbClientAuthFacebookStrategy() = default;
            virtual ~HbClientAuthFacebookStrategy() = default;

            void setConfig( const HbO2ClientConfig & config );

            virtual authstgy type() const final;

            virtual bool prepareAuthContract( HbClientAuthLoginObject * login_object );

        public slots:
            void onFacebookOpenBrower( const QUrl & url );
            void onFacebookLinkSucceed();
            void onFacebookLinkFailed();
        private:
            QHash< HbO2ClientFacebook *, networkuid > mPendingCodes;
            HbO2ClientConfig mConfig;
        };
    }
}

using hb::network::HbClientAuthFacebookStrategy;

#endif // HBCLIENTAUTHFACEBOOKSTRATEGY_H
