#ifndef HBTCPCLIENT_H
#define HBTCPCLIENT_H

/*! \file HbTcpClient.h */

// Local
#include <com/HbAbstractClient.h>
#include <config/com/HbTcpClientConfig.h>

namespace hb
{
    namespace network
    {
        class HbTcpSocket;

        /*!
         * TODOC
         */
        class HB_NETWORK_DECL HbTcpClient : public HbAbstractClient
        {
            Q_OBJECT
            Q_DISABLE_COPY( HbTcpClient )

        public:

            HbTcpClient( QObject * parent = nullptr );
            virtual ~HbTcpClient();

            using HbAbstractClient::join;
            virtual bool join( const HbTcpClientConfig & config ) final;
            virtual networkuid uid() const final;
            virtual HbNetworkProtocol::NetworkType type() const final;

            virtual bool setConfiguration( const HbTcpClientConfig & config ) final;
            virtual const HbTcpClientConfig & configuration() const final;

        signals:
            void socketError( QAbstractSocket::SocketError error, QString error_str );

        private:

            bool connectToNetwork() override;
            void disconnectFromNetwork() override;
            void deleteSocket() override;

            HbAbstractSocket * pendingConnection() override;
            HbAbstractSocket * currentConnection() const override;

        private:
            HbTcpSocket * mpSocket;
            HbTcpClientConfig mConfig;
        };
    }
}

using hb::network::HbTcpClient;

#endif // HBTCPCLIENT_H