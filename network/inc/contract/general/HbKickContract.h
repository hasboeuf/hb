/****************************************************************************
** Copyright (C) 2012-2015 Adrien Gavignet (hasboeuf)
** Contact: adrien.gavignet@gmail.com
**
** This file is part of the Hb module. Provided "AS IS", WITHOUT WARRANTIES
** OR CONDITIONS OF ANY KIND, either express or implied.
****************************************************************************/

#ifndef HBKICKCONTRACT_H
#define HBKICKCONTRACT_H

// Qt
// Hb
#include <HbGlobal.h>
#include <contract/HbNetworkProtocol.h>
// Local
#include <HbNetwork.h>
#include <contract/HbNetworkContract.h>

namespace hb
{
    namespace network
    {
        class HB_NETWORK_DECL HbKickContract final : public HbNetworkContract
        {

        public:
            HbKickContract();
            virtual ~HbKickContract() = default;
            HbKickContract( const HbKickContract & source );
            HbKickContract & operator=( const HbKickContract & source );

            HbKickContract * create() const;

            virtual bool read ( QDataStream & stream );
            virtual bool write( QDataStream & stream ) const;

            void setReason   ( netwint reason );
            void setDescription( const QString & description );

            netwint reason() const;
            const QString & description() const;

        private:
            netwint mReason;
            QString mDescription;
        };
    }
}

using hb::network::HbKickContract;

#endif // HBKICKCONTRACT_H
