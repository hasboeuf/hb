/****************************************************************************
** Copyright (C) 2012-2015 Adrien Gavignet (hasboeuf)
** Contact: adrien.gavignet@gmail.com
**
** This file is part of the Hb module. Provided "AS IS", WITHOUT WARRANTIES
** OR CONDITIONS OF ANY KIND, either express or implied.
****************************************************************************/

#ifndef HBABSTRACTSOCKET_H
#define HBABSTRACTSOCKET_H

// Qt
#include <QtNetwork/QAbstractSocket>
#include <QtCore/QQueue>
#include <QtCore/QPointer>
// Hb
#include <HbGlobal.h>

class QIODevice;

namespace hb
{
	namespace network
	{
		class HbAbstractSocket : public QObject
		{
			Q_OBJECT
            Q_DISABLE_COPY( HbAbstractSocket )

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

            virtual quint16 uuid() const final;
			virtual SocketType type() const = 0;
			virtual bool isListening() const = 0;

            virtual QAbstractSocket::SocketError error() const = 0;
            virtual QAbstractSocket::SocketState state() const = 0;
            virtual QString errorString() const final;

			virtual QByteArray readPacket     () final;
			virtual qint64     writePacket    (const QByteArray & packet) const final;
			virtual bool       packetAvailable() const final;

		signals:
            void socketReadyPacket ();
            void socketStateChanged(); // Used in children.
            void socketError       (); // Used in children.
            void socketConnected   (); // Used in childen.
            void socketDisconnected(); // Used in children.

		protected:

			HbAbstractSocket() = delete;
			HbAbstractSocket(QIODevice * device);

            virtual qint64 readStream ( QDataStream & stream ) final;
            virtual qint64 writeBuffer( const QByteArray & buffer ) const final;

        protected callbacks :
            // From children device.
            virtual void onReadyRead() = 0;

		private:
			quint16 _uuid;
            QPointer< QIODevice > _device;

			quint32 _bytesPending;
			QQueue< QByteArray > _packets;

		};
	}
}

#endif // HBABSTRACTSOCKET_H
