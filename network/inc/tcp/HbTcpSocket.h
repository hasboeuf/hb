#ifndef HBTCPSOCKET_H
#define HBTCPSOCKET_H

// Local
#include <HbAbstractSocket.h>
#include <tcp/HbTcpConfig.h>

class QTcpSocket;

namespace hb
{
	namespace network
	{

		class HbTcpSocket final : public HbAbstractSocket
		{
			Q_OBJECT
			Q_DISABLE_COPY( HbTcpSocket )

		private:

		public:

			HbTcpSocket() = delete;
			HbTcpSocket( QTcpSocket * device );
			virtual ~HbTcpSocket();

			SocketType type() const;

			bool connectToHost(const HbTcpConfig & config);
			bool disconnectFromHost();

			bool isListening() const;

			void setSocketOption(QAbstractSocket::SocketOption option, bool enable);
			bool socketOption(QAbstractSocket::SocketOption option) const;

            QAbstractSocket::SocketError error() const;
            QAbstractSocket::SocketState state() const;

        private callbacks :
            // From device.
            void onReadyRead();
            void onStateChanged(QAbstractSocket::SocketState state);

		private:
			HbTcpConfig _config;
            QTcpSocket * _device;
		};
	}
}

#endif // HBTCPSOCKET_H
