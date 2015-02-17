/****************************************************************************
** Copyright (C) 2012-2015 Adrien Gavignet (hasboeuf)
** Contact: adrien.gavignet@gmail.com
**
** This file is part of the Hb module. Provided "AS IS", WITHOUT WARRANTIES
** OR CONDITIONS OF ANY KIND, either express or implied.
****************************************************************************/

#ifndef HBAUTHREQUESTCONTRACT_H
#define HBAUTHREQUESTCONTRACT_H

// Qt
#include <QtCore/QObject>
#include <QtCore/QSet>
// Hb
#include <HbGlobal.h>
// Local
#include <HbNetwork.h>
#include <contract/HbNetworkContract.h>
#include <contract/auth/HbAuthStatusContract.h> // Covariance.

namespace hb
{
    namespace network
    {

        class HB_NETWORK_DECL HbAuthRequestContract : public HbNetworkContract
        {

        public:

            HbAuthRequestContract();
            virtual ~HbAuthRequestContract() = default;
            HbAuthRequestContract( const HbAuthRequestContract & source );
            HbAuthRequestContract & operator=( const HbAuthRequestContract & source );

            HbAuthRequestContract * create() const = 0;

            HbAuthStatusContract * reply() const;

            virtual bool read ( QDataStream & stream );
            virtual bool write( QDataStream & stream ) const;

            virtual authstgy type() const final;
            virtual void setType( authstgy type ) final;

        protected:
            authstgy mType;
        };
    }
}

using hb::network::HbAuthRequestContract;

#endif // HBAUTHREQUESTCONTRACT_H
