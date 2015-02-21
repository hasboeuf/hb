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
#include <contract/HbComContract.h>
// Local
#include <HbAbstractServer.h> // Covariance.

namespace hb
{
    namespace com
    {
        class HbAbstractSocket;

        class HbSocketHandler : public QObject, public HbUid< netwuid, CLASS_NETW >
        {
            Q_OBJECT
            Q_DISABLE_COPY( HbSocketHandler )
            Q_FRIEND_CLASS( HbAbstractServer )

        public:
            virtual bool canHandleNewConnection() final;

        protected:
            enum HandlerState
            {
                NOT_THREADED = 0,
                THREADED
            };

            HbSocketHandler( HbAbstractServer * server );
            virtual ~HbSocketHandler();

            virtual HbAbstractServer * server() const; // TODO = 0 ???

            virtual bool storeNewSocket(HbAbstractSocket * socket , qint32 previous_uid ) final;

        protected:
            virtual void reset();

        protected:
            HandlerState       mState;

            QHash< sockuid, HbAbstractSocket * > mSocketById;
            QHash< HbAbstractSocket *, sockuid > mIdBySocket;

            QMutex       mSocketMutex;

        private:
            HbAbstractServer * mpServer; // SUB

        public slots:
            // From QThread
            virtual void init();
            // From Server
            virtual void onNewPendingConnection( qint32 socket_descriptor ) = 0;
            virtual void onDisconnectionRequest( quint16 uid );
            virtual void onServerLeft();
            virtual void onSendContract( ShConstHbComContract contract ); // Send to all.
            virtual void onSendContract( sockuid socket_uid, ShConstHbComContract contract );
            // From Socket
            virtual void onSocketReadyPacket();
            virtual void onSocketDisconnected();


        signals:
            // To Server.
            void handlerIdled          ();
            void socketConnected       ( qint32 socket_previous_id, sockuid socket_id );
            void socketDisconnected    ( sockuid socket_uid );
            void socketContractReceived( sockuid socket_uid, const HbComContract * contract );
        };
    }
}

#endif // HBSOCKETHANDLER_H
