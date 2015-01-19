/****************************************************************************
** Copyright (C) 2012-2015 Adrien Gavignet (hasboeuf)
** Contact: adrien.gavignet@gmail.com
**
** This file is part of the Hb module. Provided "AS IS", WITHOUT WARRANTIES
** OR CONDITIONS OF ANY KIND, either express or implied.
****************************************************************************/

#ifndef HBABSTRACTCLIENT_H
#define HBABSTRACTCLIENT_H

// Hb
#include <HbGlobal.h>
// Local
#include <HbNetwork.h>
#include <com/HbAbstractNetwork.h>

namespace hb
{
	namespace network
	{

		class HbAbstractSocket;


		class HB_NETWORK_DECL HbAbstractClient : public HbAbstractNetwork
		{
			Q_OBJECT
            Q_DISABLE_COPY( HbAbstractClient )

		public:

			virtual bool join () final;
			virtual bool leave() final;
            virtual bool isReady() const final;

			virtual bool send(const HbNetworkContract * contract);
			//virtual bool reply(int sender, const HbNetworkContract * contract);

		signals:
            void connected();
			void disconnected();

		protected:
			HbAbstractClient(QObject * parent = nullptr);
			virtual ~HbAbstractClient() = default;

			virtual bool connectToNetwork() = 0;
			virtual bool disconnectFromNetwork() = 0;
            virtual void deleteSocket() = 0;

			virtual HbAbstractSocket * pendingConnection() = 0;
			virtual HbAbstractSocket * currentConnection() const = 0;

		private:
			void timerEvent(QTimerEvent * event);

		private callbacks : // From device.
            void onSocketConnected();
            void onSocketDisconnected();
            void onSocketContractReceived( const HbNetworkContract& contract );

		private:
			qint32 _retry;
			bool _ready;
		};


	}
}

#endif // HBABSTRACTCLIENT_H