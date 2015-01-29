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
        class HbSocketHandler;

		class HB_NETWORK_DECL HbAbstractServer : public HbAbstractNetwork
		{
			Q_OBJECT
			Q_DISABLE_COPY( HbAbstractServer )
			Q_FRIEND_CLASS( HbSocketHandler )

		public:
            virtual ~HbAbstractServer() = default; // TODO CHECK

            virtual bool join () final;
			virtual bool leave() final;
			virtual bool leave( quint16 uuid ) final;
            virtual bool isReady() const final;
            virtual quint16 uuid() const final;
            virtual HbNetworkProtocol::NetworkType type() const = 0;

            virtual bool send( HbNetworkContract * contract );
			//virtual bool reply(int sender, const HbNetworkContract * contract);
			//virtual bool forward(int receiver, HbNetworkContract * contract);

            virtual bool isUuidConnected( quint16 uuid ) const final;

			//virtual const HbServerConfig & configuration() const = 0;
            virtual const HbServerConfig & configuration() const; // SUB
	
		protected:
			HbAbstractServer(QObject * parent = nullptr);


			virtual bool connectToNetwork() = 0;
			virtual void disconnectFromNetwork() = 0;
			virtual bool isListening() const = 0; // From device.

			//virtual void incomingConnection(HbAbstractSocket * socket); to handler
			virtual bool disconnectFromNetwork( quint16 uuid ) = 0;

            virtual void reset();

        signals:
            void serverConnected   ( quint16 server_uuid );
            void serverDisconnected( quint16 server_uuid );
            // To higher level class.
            void socketConnected       ( quint16 server_uuid, sockuuid socket_uuid );
            void socketDisconnected    ( quint16 server_uuid, sockuuid socket_uuid );
            void socketContractReceived( quint16 server_uuid, sockuuid socket_uuid, const HbNetworkContract * contract );

        public callbacks :
            // From HbSocketHandler.
            void onSocketConnected       ( qint32 socket_descriptor, sockuuid socket_uuid );
            void onSocketDisconnected    ( sockuuid socket_uuid );
            void onSocketContractReceived( sockuuid socket_uuid, const HbNetworkContract * contract );
            void onHandlerIdled();

		private:
            HbServerConfig mConfig; // SUB
            netwuuid mUuid;
            bool mReady;

		protected:
            QList< qint32 > mPending; // Socket descriptors not instanciated.
            QHash< sockuuid, HbSocketHandler * > mHandlerBySocketId;
            QHash< netwuuid, HbSocketHandler * > mHandlerById;
		};
	}
}

#endif // HBABSTRACTSERVER_H
