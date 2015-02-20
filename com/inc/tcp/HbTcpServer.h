#ifndef HBTCPSERVER_H
#define HBTCPSERVER_H

// Qt
#include <QtNetwork/QTcpServer>
// Local
#include <HbAbstractServer.h>
#include <config/HbTcpServerConfig.h>

class QTcpServer;

namespace hb
{
    namespace com
    {
        class HbTcpSocketHandler;

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

        class HB_COM_DECL HbTcpServer : public HbAbstractServer
        {
            Q_OBJECT
            Q_DISABLE_COPY( HbTcpServer )

        public :

            HbTcpServer( QObject * parent = nullptr );
            virtual ~HbTcpServer();

            using HbAbstractServer::join;
            virtual bool join( const HbTcpServerConfig & config ) final;

            virtual bool setConfiguration( const HbTcpServerConfig & config ) final;
            virtual const HbTcpServerConfig & configuration() const final;

        private :
            virtual bool connectToCom();
            virtual void disconnectFromCom();
            virtual bool isListening() const;
            virtual HbComProtocol::ComType type() const;

            //void incomingConnection( HbAbstractSocket * socket ); to handler
            bool disconnectFromCom( quint16 uid );

            virtual void reset() final;

        private callbacks:
            // From device.
            void onNewConnection( qint32 socket_descriptor );

        signals:
            // To HbTcpSocketHandler.
            void newConnection( qint32 socket_descriptor );

        private :

            TcpServer * mpDevice;
            HbTcpServerConfig mConfig;
        };
    }
}

using hb::com::HbTcpServer;

#endif // HBTCPSERVER_H
