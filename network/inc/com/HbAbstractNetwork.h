/****************************************************************************
** Copyright (C) 2012-2015 Adrien Gavignet (hasboeuf)
** Contact: adrien.gavignet@gmail.com
**
** This file is part of the Hb module. Provided "AS IS", WITHOUT WARRANTIES
** OR CONDITIONS OF ANY KIND, either express or implied.
****************************************************************************/

#ifndef HBABSTRACTNETWORK_H
#define HBABSTRACTNETWORK_H

// Qt
#include <QtNetwork/QAbstractSocket>
//#include <QtCore/QHash>
// Hb
#include <HbGlobal.h>
// Local
#include <HbNetwork.h>
#include <contract/HbNetworkContract.h>
#include <config/HbNetworkConfig.h>

namespace hb
{
	namespace network
	{

		class IHbNetworkListener;

		class HB_NETWORK_DECL HbAbstractNetwork : public QObject
		{
			Q_OBJECT
			Q_DISABLE_COPY( HbAbstractNetwork )

		public:

			virtual bool join() = 0;
			virtual bool leave() = 0;
            virtual bool isReady() const = 0;
            virtual quint16 uuid() const = 0;

			//virtual void addListener(IHbNetworkListener * listener) final;
			//virtual void removeListener(IHbNetworkListener * listener) final;

            virtual bool send( HbNetworkContract * contract ) = 0;
			//virtual bool reply(int sender, const HbNetworkContract * contract) = 0;

			//virtual const HbNetworkConfig & configuration() const = 0; SUB
            virtual const HbNetworkConfig & configuration() const;

		protected:
			HbAbstractNetwork(QObject * parent = nullptr);
			virtual ~HbAbstractNetwork() = default;

			//virtual const QList< IHbNetworkListener * > & listeners() const final;

		private:
            HbNetworkConfig mConfig; // SUB
            //QList< IHbNetworkListener * > mListeners;

		};
	}
}

#endif // HBABSTRACTNETWORK_H
