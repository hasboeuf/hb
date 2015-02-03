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

namespace hb
{
    namespace network
    {
        class HB_NETWORK_DECL HbAuthRequestContract final : public HbNetworkContract
        {

        public:

            HbAuthRequestContract();
            virtual ~HbAuthRequestContract() = default;
            HbAuthRequestContract( const HbAuthRequestContract & source );
            HbAuthRequestContract & operator=( const HbAuthRequestContract & source );

            HbAuthRequestContract * create() const;

            virtual bool read ( QDataStream & stream );
            virtual bool write( QDataStream & stream ) const;

            QString username() const;
            QString passwork() const;
            void setUsername( QString username );
            void setPassword( QString password );

        private:
            QString mUsername;
            QString mPassword;

        };
    }
}

using hb::network::HbAuthRequestContract;

#endif // HBAUTHREQUESTCONTRACT_H
