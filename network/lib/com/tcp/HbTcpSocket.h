#ifndef HBTCPSOCKET_H
#define HBTCPSOCKET_H

/*! \file HbTcpSocket.h */

// Local
#include <com/HbAbstractSocket.h>
#include <config/com/HbTcpConfig.h>

class QTcpSocket;

namespace hb
{
    namespace network
    {

        /*!
         * TODOC
         */
        class HbTcpSocket final : public HbAbstractSocket
        {
            Q_OBJECT
            Q_DISABLE_COPY( HbTcpSocket )

        private:

        public:

            HbTcpSocket() = delete;
            HbTcpSocket( QTcpSocket * device );
            virtual ~HbTcpSocket();

            HbNetworkProtocol::NetworkType type() const override;

            bool leave() override;
            bool connectToHost( const HbTcpConfig & config );


            bool isListening() const override;

            void setSocketOption(QAbstractSocket::SocketOption option, bool enable);
            bool socketOption(QAbstractSocket::SocketOption option) const;

            QAbstractSocket::SocketError error() const override;
            QAbstractSocket::SocketState state() const override;

        private callbacks:
            // From device.
            void onReadyRead();
            void onStateChanged(QAbstractSocket::SocketState state);

        private:
            HbTcpConfig mConfig;
            QTcpSocket * mpDevice;
        };
    }
}

#endif // HBTCPSOCKET_H