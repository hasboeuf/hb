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
        class HB_NETWORK_DECL HbAuthRequestContract : public HbNetworkContract
        {

        public:

            enum AuthType : quint8
            {
                AUTH_NONE = 0,
                AUTH_USER,
                AUTH_FACEOOK
            };

            HbAuthRequestContract();
            virtual ~HbAuthRequestContract() = default;
            HbAuthRequestContract( const HbAuthRequestContract & source );
            HbAuthRequestContract & operator=( const HbAuthRequestContract & source );

            HbAuthRequestContract * create() const = 0;

            virtual bool read ( QDataStream & stream );
            virtual bool write( QDataStream & stream ) const;

            virtual AuthType type() const final;
            virtual void setType( AuthType type ) final;

        protected:
            AuthType mType;
        };
    }
}

using hb::network::HbAuthRequestContract;

#endif // HBAUTHREQUESTCONTRACT_H
