/****************************************************************************
** Copyright (C) 2012-2015 Adrien Gavignet (hasboeuf)
** Contact: adrien.gavignet@gmail.com
**
** This file is part of the Hb module. Provided "AS IS", WITHOUT WARRANTIES
** OR CONDITIONS OF ANY KIND, either express or implied.
****************************************************************************/

#ifndef HBSOCKETHANDLER_H
#define HBSOCKETHANDLER_H

// Qt
#include <QtCore/QObject>
#include <QtCore/QMap>
#include <QtCore/QMutex>
// Hb
#include <HbGlobal.h>
#include <contract/HbNetworkContract.h>
// Local
#include <com/HbAbstractServer.h> // Covariance.

namespace hb
{
	namespace network
    {
		class HbAbstractSocket;

        class HbSocketHandler : public QObject
        {
			Q_OBJECT
			Q_DISABLE_COPY( HbSocketHandler )
			Q_FRIEND_CLASS( HbAbstractServer )

        public:
            virtual quint16  id() const final;
            virtual bool canHandleNewConnection() final;

        protected:
			enum HandlerState
			{
				NOT_THREADED = 0,
				THREADED
			};

			HbSocketHandler( HbAbstractServer * server );
			virtual ~HbSocketHandler();

			//virtual HbAbstractServer * server( ) const = 0;
			virtual HbAbstractServer * server() const;

            virtual bool storeNewSocket(HbAbstractSocket * socket , qint32 previous_uuid ) final;

        protected:
            virtual void reset();

        protected:
            quint16            mId;
			HandlerState       mState;

			QMap<quint16, HbAbstractSocket *> mSocketById;
			QMap<HbAbstractSocket *, quint16> mIdBySocket;

            QMutex       mSocketMutex;

		private:
			HbAbstractServer * mpServer; // SUB

        public slots:
            // From QThread
            virtual void init();
            // From Server
            virtual void onNewPendingConnection( qint32 socket_descriptor ) = 0;
            virtual void onDisconnectionRequest( quint16 uuid );
            virtual void onServerLeft();
			// From Socket
			virtual void onSocketReadyPacket();
			virtual void onSocketDisconnected();


		signals:
            // To Server.
            void handlerIdled          ();
            void socketConnected       ( qint32 socket_previous_id, quint16 socket_id );
            void socketDisconnected    ( quint16 socket_uuid );
            void socketContractReceived( quint16 socket_uuid, const HbNetworkContract * contract );
        };
    }
}

#endif // HBSOCKETHANDLER_H
