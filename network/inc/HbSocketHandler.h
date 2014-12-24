#ifndef HBSOCKETHANDLER_H
#define HBSOCKETHANDLER_H

// Qt
#include <QtCore/QObject>
#include <QtCore/QMap>
// Hb
#include <HbGlobal.h>
#include <HbNetworkContract.h>
// Local
#include <HbAbstractServer.h> // Covariance.

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

            virtual quint16  id() const final;
            virtual bool canHandleNewConnection() const final;
			virtual bool storeNewSocket( HbAbstractSocket * socket ) final;

        protected:
            quint16            mId;
			HandlerState       mState;

			QMap<quint16, HbAbstractSocket *> mSocketById;
			QMap<HbAbstractSocket *, quint16> mIdBySocket;

		private:
			HbAbstractServer * mpServer; // SUB

        public callbacks:
            // From QThread
            virtual void init() = 0;

			// From Server
			virtual void onNewPendingConnection( qint32 socket_descriptor ) = 0;
			// From Socket
			virtual void onSocketReadyPacket();
			virtual void onSocketDisconnected();

		signals:
			void socketConnected( int socket_descriptor, quint16 socket_id );
			void socketDisconnected( quint16 socket_id );
			void socketContractReceived( const HbNetworkContract& contract );
        };
    }
}

#endif // HBSOCKETHANDLER_H
