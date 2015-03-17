/****************************************************************************
** Copyright (C) 2012-2015 Adrien Gavignet (hasboeuf)
** Contact: adrien.gavignet@gmail.com
**
** This file is part of the Hb module. Provided "AS IS", WITHOUT WARRANTIES
** OR CONDITIONS OF ANY KIND, either express or implied.
****************************************************************************/

#ifndef HBAUTHFACEBOOKREQUESTCONTRACT_H
#define HBAUTHFACEBOOKREQUESTCONTRACT_H

/*! \file HbAuthFacebookRequestContract.h */

// Qt
#include <QtCore/QObject>
#include <QtCore/QSet>
// Hb
#include <HbGlobal.h>
#include <facebook/HbO2ClientFacebook.h>
// Local
#include <HbNetwork.h>
#include <contract/auth/HbAuthRequestContract.h>

namespace hb
{
    namespace network
    {
        /*!
         * TODOC
         */
        class HB_NETWORK_DECL HbAuthFacebookRequestContract : public HbAuthRequestContract
        {

        public:

            HbAuthFacebookRequestContract();
            virtual ~HbAuthFacebookRequestContract() = default;
            HbAuthFacebookRequestContract( const HbAuthFacebookRequestContract & source );
            HbAuthFacebookRequestContract & operator=( const HbAuthFacebookRequestContract & source );

            HbAuthFacebookRequestContract * create() const;

            virtual bool read ( QDataStream & stream );
            virtual bool write( QDataStream & stream ) const;

            virtual const HbO2ClientFacebook & client() const final;
            virtual void setClient( const HbO2ClientFacebook & client ) final;

        protected:
            HbO2ClientFacebook mClient;
        };
    }
}

using hb::network::HbAuthFacebookRequestContract;

#endif // HBAUTHFACEBOOKREQUESTCONTRACT_H
