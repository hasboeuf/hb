/****************************************************************************
** Copyright (C) 2012-2015 Adrien Gavignet (hasboeuf)
** Contact: adrien.gavignet@gmail.com
**
** This file is part of the Hb module. Provided "AS IS", WITHOUT WARRANTIES
** OR CONDITIONS OF ANY KIND, either express or implied.
****************************************************************************/

#ifndef HBOAUTHREQUESTCONTRACT_H
#define HBOAUTHREQUESTCONTRACT_H

// Qt
#include <QtCore/QObject>
#include <QtCore/QSet>
// Hb
#include <HbGlobal.h>
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
        class HB_NETWORK_DECL HbOAuthRequestContract : public HbAuthRequestContract
        {

        public:

            HbOAuthRequestContract();
            virtual ~HbOAuthRequestContract() = default;
            HbOAuthRequestContract( const HbOAuthRequestContract & source );
            HbOAuthRequestContract & operator=( const HbOAuthRequestContract & source );

            virtual HbOAuthRequestContract * create() const override;

            virtual bool read ( QDataStream & stream ) override;
            virtual bool write( QDataStream & stream ) const override;

            const QString & code() const;
            const QString & redirectUri() const;

            void setCode( const QString & code );
            void setRedirectUri( const QString & redirect_uri );

        protected:
            QString    mCode;
            QString    mRedirectUri;
        };
    }
}

using hb::network::HbOAuthRequestContract;

#endif // HBOAUTHREQUESTCONTRACT_H
