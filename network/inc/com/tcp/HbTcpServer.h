#ifndef HBTCPSERVER_H
#define HBTCPSERVER_H

/*! \file HbTcpServer.h */

// Qt
#include <QtNetwork/QTcpServer>
// Local
#include <com/HbAbstractServer.h>
#include <config/com/HbTcpServerConfig.h>

namespace hb
{
    namespace network
    {
        /*!
         * TODOC
         */
        class TcpServer final : public QTcpServer
        {
            Q_OBJECT
            Q_DISABLE_COPY( TcpServer )
            Q_FRIEND_CLASS( HbTcpServer )

        protected:
            TcpServer( QObject * parent = nullptr );
            void incomingConnection( qint32 socket_descriptor );
        signals:
            void newConnection( qint32 socket_descriptor );
        };

        class HB_NETWORK_DECL HbTcpServer : public HbAbstractServer
        {
            Q_OBJECT
            Q_DISABLE_COPY( HbTcpServer )

        public:

            HbTcpServer( QObject * parent = nullptr );
            virtual ~HbTcpServer();

            using HbAbstractServer::join;
            virtual bool join( const HbTcpServerConfig & config ) final;

            virtual bool setConfiguration( const HbTcpServerConfig & config ) final;
            virtual const HbTcpServerConfig & configuration() const final;

        private:
            virtual bool connectToNetwork() override;
            virtual void disconnectFromNetwork() override;
            virtual bool isListening() const override;
            virtual HbNetworkProtocol::NetworkType type() const override;

            virtual void reset() final;

        private callbacks:
            // From device.
            void onNewConnection( qint32 socket_descriptor );

        signals:
            // To HbTcpSocketHandler.
            void newConnection( qint32 socket_descriptor );

        private:

            TcpServer * mpDevice;
            HbTcpServerConfig mConfig;
        };
    }
}

using hb::network::HbTcpServer;

#endif // HBTCPSERVER_H
