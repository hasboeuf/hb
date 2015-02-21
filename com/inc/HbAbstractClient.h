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
#include <HbCom.h>
#include <HbAbstractCom.h>
#include <config/HbClientConfig.h>

namespace hb
{
    namespace com
    {

        class HbAbstractSocket;


        class HB_COM_DECL HbAbstractClient : public HbAbstractCom
        {
            Q_OBJECT
            Q_DISABLE_COPY( HbAbstractClient )

        public:

            virtual bool join () final;
            virtual bool leave() final;
            virtual bool isReady() const final;
            virtual sockuid uid() const = 0;
            virtual HbComProtocol::ComType type() const = 0;

            virtual bool send( ShConstHbComContract contract);

            virtual const HbClientConfig & configuration() const; // SUB

        signals:
            void clientConnected         ( sockuid client_uid );
            void clientDisconnected      ( sockuid client_uid );
            void clientContractReceived  ( sockuid client_uid, const HbComContract * contract );

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
            void onSocketReadyPacket();
            void onSocketDisconnected();            

        private:
            HbClientConfig mConfig; // SUB
            qint32 mRetry;
            bool mReady;
        };


    }
}

#endif // HBABSTRACTCLIENT_H
