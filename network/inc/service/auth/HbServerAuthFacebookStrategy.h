/****************************************************************************
** Copyright (C) 2012-2015 Adrien Gavignet (hasboeuf)
** Contact: adrien.gavignet@gmail.com
**
** This file is part of the Hb module. Provided "AS IS", WITHOUT WARRANTIES
** OR CONDITIONS OF ANY KIND, either express or implied.
****************************************************************************/

#ifndef HBSERVERAUTHFACEBOOKSTRATEGY_H
#define HBSERVERAUTHFACEBOOKSTRATEGY_H

/*! \file HbServerAuthFacebookStrategy.h */

// Qt
#include <QtCore/QHash>
// Hb
#include <facebook/HbFacebookRequester.h>
#include <config/HbO2ServerConfig.h>
// Local
#include <HbNetwork.h>
#include <service/auth/HbServerOAuthStrategy.h>
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

        /*!
         * TODOC
         */
        class HB_NETWORK_DECL HbServerAuthFacebookStrategy : public HbServerOAuthStrategy
        {
            Q_OBJECT
        public:

            HbServerAuthFacebookStrategy();
            virtual ~HbServerAuthFacebookStrategy() = default;

            virtual authstgy type() const final;
            virtual bool checkLogin( const HbAuthRequestContract * contract ) override;

        public slots:
            void onLinkSucceed();
            void onRequestCompleted( quint64 request_id, HbFacebookObject * object );

        private:
            HbFacebookRequester mRequester;
        };
    }
}

using hb::network::HbServerAuthFacebookStrategy;

#endif // HBSERVERAUTHFACEBOOKSTRATEGY_H
