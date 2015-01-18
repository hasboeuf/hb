/****************************************************************************
** Copyright (C) 2012-2015 Adrien Gavignet (hasboeuf)
** Contact: adrien.gavignet@gmail.com
**
** This file is part of the Hb module. Provided "AS IS", WITHOUT WARRANTIES
** OR CONDITIONS OF ANY KIND, either express or implied.
****************************************************************************/

#ifndef HBCONNECTIONCONTRACT_H
#define HBCONNECTIONCONTRACT_H

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


        class HB_NETWORK_DECL HbConnectionContract : public HbNetworkContract
		{

		public:

            virtual bool read(QDataStream & stream);
            virtual bool write(QDataStream & stream) const;

		protected:
            HbConnectionContract() = delete;
            HbConnectionContract( Service service, Code code );
            virtual ~HbConnectionContract() = default;

		private:


		};


	}
}

using hb::network::HbConnectionContract;

#endif // HBCONNECTIONCONTRACT_H
