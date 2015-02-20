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
// Hb
#include <core/HbUid.h>
// Local
#include <HbAbstractCom.h>
#include <config/HbServerConfig.h>

namespace hb
{
    namespace com
    {

        class HbAbstractSocket;
        class HbSocketHandler;

        class HB_COM_DECL HbAbstractServer : public HbAbstractCom, public HbUid< netwuid, CLASS_NETW >
        {
            Q_OBJECT
            Q_DISABLE_COPY( HbAbstractServer )
            Q_FRIEND_CLASS( HbSocketHandler )

        public:
            virtual ~HbAbstractServer() = default; // TODO CHECK

            virtual bool join () final;
            virtual bool leave() final;
            virtual bool leave( quint16 uid ) final;
            virtual bool isReady() const final;
            virtual HbComProtocol::ComType type() const = 0;

            virtual bool send( HbComContract * contract );
            //virtual bool reply(int sender, const HbComContract * contract);
            //virtual bool forward(int receiver, HbComContract * contract);

            virtual bool isUidConnected( quint16 uid ) const final;

            //virtual const HbServerConfig & configuration() const = 0;
            virtual const HbServerConfig & configuration() const; // SUB
    
        protected:
            HbAbstractServer(QObject * parent = nullptr);


            virtual bool connectToCom() = 0;
            virtual void disconnectFromCom() = 0;
            virtual bool isListening() const = 0; // From device.

            //virtual void incomingConnection(HbAbstractSocket * socket); to handler
            virtual bool disconnectFromCom( quint16 uid ) = 0;

            virtual void reset();

        signals:
            void serverConnected   ( servuid server_uid );
            void serverDisconnected( servuid server_uid );
            // To higher level class.
            void socketConnected       ( servuid server_uid, sockuid socket_uid );
            void socketDisconnected    ( servuid server_uid, sockuid socket_uid );
            void socketContractReceived( servuid server_uid, sockuid socket_uid, const HbComContract * contract );

        public callbacks :
            // From HbSocketHandler.
            void onSocketConnected       ( qint32 socket_descriptor, sockuid socket_uid );
            void onSocketDisconnected    ( sockuid socket_uid );
            void onSocketContractReceived( sockuid socket_uid, const HbComContract * contract );
            void onHandlerIdled();

        private:
            HbServerConfig mConfig; // SUB
            bool mReady;

        protected:
            QList< qint32 > mPending; // Socket descriptors not instanciated.
            QHash< sockuid, HbSocketHandler * > mHandlerBySocketId;
            QHash< netwuid, HbSocketHandler * > mHandlerById;
        };
    }
}

#endif // HBABSTRACTSERVER_H
