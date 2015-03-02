/****************************************************************************
** Copyright (C) 2012-2015 Adrien Gavignet (hasboeuf)
** Contact: adrien.gavignet@gmail.com
**
** This file is part of the Hb module. Provided "AS IS", WITHOUT WARRANTIES
** OR CONDITIONS OF ANY KIND, either express or implied.
****************************************************************************/

#ifndef HBSERVERAUTHFACEBOOKSTRATEGY_H
#define HBSERVERAUTHFACEBOOKSTRATEGY_H

// Qt
#include <QtCore/QHash>
// Hb
#include <facebook/HbFacebookRequester.h>
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
        class HbO2ServerFacebook;
    }

    using namespace link;

    namespace network
    {
        class HbAuthRequestContract;

        class HB_NETWORK_DECL HbServerAuthFacebookStrategy : public HbServerAuthStrategy
        {
            Q_OBJECT
        public:

            HbServerAuthFacebookStrategy();
            virtual ~HbServerAuthFacebookStrategy() = default;

            void setConfig( const HbO2ServerConfig & config );

            virtual authstgy type() const final;
            virtual bool checkLogin( const HbAuthRequestContract * contract );

        public slots:
            void onLinkSucceed();
            void onLinkFailed( const QString & error );
            void onRequestCompleted( quint64 request_id, HbFacebookObject * object );

        private:
            HbFacebookRequester                       mRequester;
            QHash< HbO2ServerFacebook *, networkuid > mPendingToken;
            QHash< quint64, networkuid >              mPendingRequest;
            HbO2ServerConfig                          mConfig;
        };
    }
}

using hb::network::HbServerAuthFacebookStrategy;

#endif // HBSERVERAUTHFACEBOOKSTRATEGY_H
