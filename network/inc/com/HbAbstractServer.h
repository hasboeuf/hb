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
#include <QtCore/QSharedPointer>
// Hb
#include <core/HbUid.h>
// Local
#include <com/HbAbstractNetwork.h>
#include <config/com/HbServerConfig.h>

namespace hb
{
    namespace network
    {

        class HbAbstractSocket;
        class HbSocketHandler;

        class HB_NETWORK_DECL HbAbstractServer : public HbAbstractNetwork, public HbUid< networkuid, CLASS_SERVER, true >
        {
            Q_OBJECT
            Q_DISABLE_COPY( HbAbstractServer )
            Q_FRIEND_CLASS( HbSocketHandler )

        public:
            virtual ~HbAbstractServer() = default; // TODO CHECK

            virtual bool join () final;
            virtual bool leave() final;
            virtual bool leave( networkuid uid ) final;
            virtual bool isReady() const final;
            virtual HbNetworkProtocol::NetworkType type() const = 0;

            virtual bool send( ShConstHbNetworkContract contract );

            virtual bool isUidConnected( networkuid uid ) const final;

            virtual const HbServerConfig & configuration() const; // SUB

        protected:
            HbAbstractServer( QObject * parent = nullptr );


            virtual bool connectToNetwork() = 0;
            virtual void disconnectFromNetwork() = 0;
            virtual bool isListening() const = 0; // From device.

            virtual bool disconnectFromNetwork( networkuid uid ) = 0;

            virtual void reset();

        signals:
            void serverConnected   ( networkuid server_uid );
            void serverDisconnected( networkuid server_uid );
            // To higher level class.
            void socketConnected       ( networkuid server_uid, networkuid socket_uid );
            void socketDisconnected    ( networkuid server_uid, networkuid socket_uid );
            void socketContractReceived( networkuid server_uid, networkuid socket_uid, const HbNetworkContract * contract );

        public callbacks :
            // From HbSocketHandler.
            void onSocketConnected       ( qint32 socket_descriptor, networkuid socket_uid );
            void onSocketDisconnected    ( networkuid socket_uid );
            void onSocketContractReceived( networkuid socket_uid, const HbNetworkContract * contract );
            void onHandlerIdled();

        private:
            HbServerConfig mConfig; // SUB
            bool mReady;

        protected:
            QList< qint32 > mPending; // Socket descriptors not instanciated.
            QHash< networkuid, HbSocketHandler * > mHandlerBySocketId;
            QHash< networkuid, HbSocketHandler * > mHandlerById;
        };
    }
}

#endif // HBABSTRACTSERVER_H
