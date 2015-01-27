#ifndef HBTCPCLIENT_H
#define HBTCPCLIENT_H

// Local
#include <com/HbAbstractClient.h>
#include <config/HbTcpClientConfig.h>

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
            virtual bool join( const HbTcpClientConfig & config ) final;
            virtual quint16 uuid() const final;

            virtual bool setConfiguration( const HbTcpClientConfig & config ) final;
            virtual const HbTcpClientConfig & configuration() const final;

        signals:
            void socketError( QAbstractSocket::SocketError error, QString error_str );

        private :

            bool connectToNetwork();
            bool disconnectFromNetwork();
            void deleteSocket();

            HbAbstractSocket * pendingConnection();
            HbAbstractSocket * currentConnection() const;

        private :

            HbTcpSocket * mpSocket;
            HbTcpClientConfig mConfig;
		};
	}
}

using hb::network::HbTcpClient;

#endif // HBTCPCLIENT_H
