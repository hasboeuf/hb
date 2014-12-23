#ifndef HBABSTRACTSOCKET_H
#define HBABSTRACTSOCKET_H

// Qt
#include <QtNetwork/QAbstractSocket>
#include <QtCore/QPointer>
#include <QtCore/QQueue>
// Hb
#include <HbErrorCode.h>
#include <HbGlobal.h>

namespace hb
{
	namespace network
	{


		class HbAbstractSocket : public QObject
		{
			Q_OBJECT
			Q_DISABLE_COPY(HbAbstractSocket)

		public:

			enum SocketType : qint16
			{
				TcpSocket = 0,
				WebSocket,
				SslSocket,
				UdpSocket,
				LocalSocket,
				BluetoothSocket
			};


		public:

			virtual ~HbAbstractSocket();

			virtual int uuid() const final;
			virtual SocketType type() const = 0;

			virtual bool isListening() const = 0;

			virtual QAbstractSocket::SocketError error() const = 0;
			virtual QAbstractSocket::SocketState state() const = 0;

			virtual QByteArray readPacket     () final;
			virtual qint64     writePacket    (const QByteArray & packet) const final;
			virtual bool       packetAvailable() const final;

			virtual QString errorString() const final;

		signals:
			void connected   ();
			void readyPacket ();
			void disconnected();

		protected:

			HbAbstractSocket() = delete;
			HbAbstractSocket(QIODevice * device);

			virtual qint64 readStream (QDataStream & stream) final;
			virtual qint64 writeBuffer(const QByteArray & buffer) const;

			virtual void setErrorString(const QString & message) final;
			virtual void setErrorString(QAbstractSocket::SocketError error) final;

		protected callbacks :
			virtual void receive() = 0;

		private:
			int _uuid;
			QPointer< QIODevice > _device;

			quint32 _bytesPending;
			QQueue< QByteArray > _packets;

			HbErrorCode _errors;
			QString _errorString;
		};


	}
}

#endif // HBABSTRACTSOCKET_H
