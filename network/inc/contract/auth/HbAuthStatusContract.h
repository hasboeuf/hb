/****************************************************************************
** Copyright (C) 2012-2015 Adrien Gavignet (hasboeuf)
** Contact: adrien.gavignet@gmail.com
**
** This file is part of the Hb module. Provided "AS IS", WITHOUT WARRANTIES
** OR CONDITIONS OF ANY KIND, either express or implied.
****************************************************************************/

#ifndef HBAUTHSTATUSCONTRACT_H
#define HBAUTHSTATUSCONTRACT_H

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
        class HB_NETWORK_DECL HbAuthStatusContract final : public HbNetworkContract
		{

		public:

            HbAuthStatusContract();
            virtual ~HbAuthStatusContract() = default;
            HbAuthStatusContract( const HbAuthStatusContract & source );
            HbAuthStatusContract & operator=( const HbAuthStatusContract & source );

            HbAuthStatusContract * create() const;

            virtual bool read ( QDataStream & stream );
            virtual bool write( QDataStream & stream ) const;

		private:

        };
	}
}

using hb::network::HbAuthStatusContract;

#endif // HBAUTHSTATUSCONTRACT_H
