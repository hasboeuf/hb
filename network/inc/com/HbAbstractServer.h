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
#include <com/HbAbstractNetwork.h>
#include <config/HbServerConfig.h>

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
				Q_DISABLE_COPY( HbNetworkPacket )


			public:
				HbNetworkPacket() = delete;
				HbNetworkPacket(const HbNetworkHeader * header, const HbNetworkContract * contract);
				virtual ~HbNetworkPacket() = default;

                //const HbNetworkHeader * header() const;
                //const HbNetworkContract * content() const;

			private:

                //const HbNetworkHeader * _header;
                //const HbNetworkContract * _content;
			};


		public:

            virtual bool join () final;
			virtual bool leave() final;
			virtual bool leave( quint16 uuid ) final;
            virtual bool isReady() const final;

            virtual bool send( const HbNetworkContract * contract );
			//virtual bool reply(int sender, const HbNetworkContract * contract);
			//virtual bool forward(int receiver, HbNetworkContract * contract);

            virtual bool isUuidConnected( quint16 uuid ) const final;

			//virtual const HbServerConfig & configuration() const = 0;
            virtual const HbServerConfig & configuration() const; // SUB
	
		protected:
			HbAbstractServer(QObject * parent = nullptr);
			virtual ~HbAbstractServer() = default;

			virtual bool connectToNetwork() = 0;
			virtual void disconnectFromNetwork() = 0;
			virtual bool isListening() const = 0; // From device.

			//virtual void incomingConnection(HbAbstractSocket * socket); to handler
			virtual bool disconnectFromNetwork( quint16 uuid ) = 0;

            virtual void reset();

		private:
            bool send( const HbNetworkPacket & packet );
			//bool send(int uuid, const HbNetworkPacket & packet);

        signals:
            void serverConnected   ( quint32 socket_uuid );
            void serverDisconnected( quint32 socket_uuid );
            // To higher level class.
            void socketConnected   ( quint32 socket_uuid );
            void socketDisconnected( quint32 socket_uuid );
            void socketContractReceived( const HbNetworkContract & contract );

        public callbacks :
            // From HbSocketHandler.
            void onSocketConnected( qint32 socket_descriptor, quint16 socket_uuid );
            void onSocketDisconnected( quint16 socket_uuid );
            void onSocketContractReceived( const HbNetworkContract& contract );
            void onHandlerIdled();

		private:
			HbServerConfig _config; // SUB
			quint32 _uuid;
			bool _ready;

		protected:
			QList< quint32 > _pending; // Socket descriptors not instanciated.
            QHash< quint32, HbSocketHandler * > mHandlerBySocketId;
            QHash< quint16, HbSocketHandler * > mHandlerById;
		};
	}
}

#endif // HBABSTRACTSERVER_H
