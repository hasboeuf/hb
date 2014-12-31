/****************************************************************************
** Copyright (C) 2012-2015 Adrien Gavignet (hasboeuf)
** Contact: adrien.gavignet@gmail.com
**
** This file is part of the Hb module. Provided "AS IS", WITHOUT WARRANTIES
** OR CONDITIONS OF ANY KIND, either express or implied.
****************************************************************************/

#ifndef HBABSTRACTSERVER_H
#define HBABSTRACTSERVER_H

// Qt
#include <QtCore/QHash>
#include <QtCore/QList>
// Local
#include <HbAbstractNetwork.h>
#include <tcp/HbServerConfig.h>

namespace hb
{
	namespace network
	{

		class HbAbstractSocket;
		class HbNetworkHeader;
        class HbSocketHandler;

		class HB_NETWORK_DECL HbAbstractServer : public HbAbstractNetwork
		{
			Q_OBJECT
			Q_DISABLE_COPY( HbAbstractServer )
			Q_FRIEND_CLASS( HbSocketHandler )

		private:

			inner class HbNetworkPacket final
			{
				Q_DISABLE_COPY(HbNetworkPacket)


			public:

				HbNetworkPacket() = delete;
				HbNetworkPacket(const HbNetworkHeader * header, const HbNetworkContract * contract);
				virtual ~HbNetworkPacket() = default;

				const HbNetworkHeader * header() const;
				const HbNetworkContract * content() const;

			private:

				const HbNetworkHeader * _header;
				const HbNetworkContract * _content;
			};


		public:

			virtual bool join() final;
			virtual bool leave() final;
			virtual bool leave(int uuid) final;
			virtual bool ready() const final;

			virtual bool send(const HbNetworkContract * contract);
			virtual bool reply(int sender, const HbNetworkContract * contract);
			//virtual bool forward(int receiver, HbNetworkContract * contract);

			virtual QList< int > connected() const final;
			virtual bool isConnected(int uuid) const final;

			//virtual const HbServerConfig & configuration() const = 0;
			virtual const HbServerConfig & configuration() const;
	
		//signals:
		//	void connected   (int uuid);
		//	void disconnected(int uuid);

		protected:

			HbAbstractServer(QObject * parent = nullptr);
			virtual ~HbAbstractServer() = default;

			virtual bool connectToNetwork() = 0;
			virtual void disconnectFromNetwork() = 0;
			virtual bool isListening() const = 0;

			//virtual void incomingConnection(HbAbstractSocket * socket); to handler
			virtual bool disconnectFromNetwork(int uuid) = 0;

			virtual void reset() = 0;

		private:

			bool send(const HbNetworkPacket & packet);
			bool send(int uuid, const HbNetworkPacket & packet);

		private callbacks :
			void onSocketConnected( int uuid );
			void onSocketDisconnected( int uuid );
			void onSocketContractReceived( const HbNetworkContract& contract );

		private:
			HbServerConfig _config; // SUB
			int _uuid;
			bool _ready;

		protected:
			QList< int > _pending;
			QHash< int, HbSocketHandler * > mHandlerBySocketId;
			QHash< HbSocketHandler *, int > mSocketByHandlerId;
		};


	}
}

#endif // HBABSTRACTSERVER_H
