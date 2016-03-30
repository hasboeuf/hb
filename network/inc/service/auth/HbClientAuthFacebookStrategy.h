/****************************************************************************
** Copyright (C) 2012-2015 Adrien Gavignet (hasboeuf)
** Contact: adrien.gavignet@gmail.com
**
** This file is part of the Hb module. Provided "AS IS", WITHOUT WARRANTIES
** OR CONDITIONS OF ANY KIND, either express or implied.
****************************************************************************/

#ifndef HBCLIENTAUTHFACEBOOKSTRATEGY_H
#define HBCLIENTAUTHFACEBOOKSTRATEGY_H

/*! \file HbClientAuthFacebookStrategy.h */

// Qt
#include <QtCore/QHash>
// Hb
#include <facebook/HbO2ClientFacebook.h>
// Local
#include <HbNetwork.h>
#include <service/auth/HbClientOAuthStrategy.h>
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
        class HB_NETWORK_DECL HbClientAuthFacebookStrategy : public HbClientOAuthStrategy
        {
            Q_OBJECT
        public:

            HbClientAuthFacebookStrategy() = default;
            virtual ~HbClientAuthFacebookStrategy() = default;

            virtual void reset() override;

            virtual void setConfig( const HbO2ClientConfig & config ) override;

            virtual authstgy type() const final;

            virtual bool prepareAuthContract( HbClientAuthLoginObject * login_object ) override;

        };
    }
}

using hb::network::HbClientAuthFacebookStrategy;

#endif // HBCLIENTAUTHFACEBOOKSTRATEGY_H
