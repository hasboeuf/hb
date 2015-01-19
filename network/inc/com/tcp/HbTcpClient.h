#ifndef HBTCPCLIENT_H
#define HBTCPCLIENT_H

// Local
#include <com/HbAbstractClient.h>
#include <config/HbTcpConfig.h>

namespace hb
{
    namespace network
	{
        class HbTcpSocket;

		class HB_NETWORK_DECL HbTcpClient : public HbAbstractClient
		{
            Q_OBJECT
			Q_DISABLE_COPY( HbTcpClient )

        public :

            HbTcpClient( QObject * parent = nullptr );
            virtual ~HbTcpClient();

			using HbAbstractClient::join;
            virtual bool join( const HbTcpConfig & config ) final;

            virtual bool setConfiguration( const HbTcpConfig & config ) final;
            virtual HbTcpConfig & configuration() final; // TODO const

        signals:
            void socketError( QAbstractSocket::SocketError error, QString error_str );

        private :

            bool connectToNetwork();
            bool disconnectFromNetwork();
            void deleteSocket();

            HbAbstractSocket * pendingConnection();
            HbAbstractSocket * currentConnection() const;

        private :

            HbTcpSocket * _socket;
            HbTcpConfig _config;
		};
	}
}

using hb::network::HbTcpClient;

#endif // HBTCPCLIENT_H
