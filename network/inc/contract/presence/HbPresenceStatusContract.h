/****************************************************************************
** Copyright (C) 2012-2015 Adrien Gavignet (hasboeuf)
** Contact: adrien.gavignet@gmail.com
**
** This file is part of the Hb module. Provided "AS IS", WITHOUT WARRANTIES
** OR CONDITIONS OF ANY KIND, either express or implied.
****************************************************************************/

#ifndef HBPRESENCESTATUSCONTRACT_H
#define HBPRESENCESTATUSCONTRACT_H

/*! \file HbPresenceStatusContract.h */

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
        /*!
         * TODOC
         */
        class HB_NETWORK_DECL HbPresenceStatusContract final : public HbNetworkContract
        {

        public:

            HbPresenceStatusContract();
            virtual ~HbPresenceStatusContract() = default;
            HbPresenceStatusContract( const HbPresenceStatusContract & source );
            HbPresenceStatusContract & operator=( const HbPresenceStatusContract & source );

            HbPresenceStatusContract * create() const;

            virtual bool read ( QDataStream & stream );
            virtual bool write( QDataStream & stream ) const;

        private:

        };
    }
}

using hb::network::HbPresenceStatusContract;

#endif // HBPRESENCESTATUSCONTRACT_H
