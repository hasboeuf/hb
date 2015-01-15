// Qt
#include <QtCore/QDataStream>
#include <QtCore/QIODevice>
// Hb
#include <HbIdGenerator.h>
#include <HbLogService.h>
// Local
#include <HbAbstractSocket.h>
#include <HbNetworkHeader.h>

using namespace hb::network;
using namespace hb::tools;

HbAbstractSocket::HbAbstractSocket(QIODevice * device)
{
    q_assert_ptr( device );
    _device = device;

    connect( _device.data(), &QIODevice::readyRead, this, &HbAbstractSocket::onReadyRead, Qt::UniqueConnection);

	_uuid = HbIdGenerator::get()->getUniqueId();

	_bytesPending = 0;
	_packets.clear();
}

HbAbstractSocket::~HbAbstractSocket()
{
    if ( !_device.isNull() )
	{
        _device->disconnect(); // Disconnect all signals.
        _device->close();
        _device->deleteLater();
	}
}

quint16 HbAbstractSocket::uuid() const
{
	return _uuid;
}


QByteArray HbAbstractSocket::readPacket()
{
    if( !_packets.isEmpty() )
    {
        return _packets.dequeue();
    }

    HbWarning( "Read an empty packet." );
    return QByteArray();
}

qint64 HbAbstractSocket::writePacket(const QByteArray & packet) const
{
    if ( !packet.isEmpty() )
	{
		QByteArray buffer;
        QDataStream stream( &buffer, QIODevice::WriteOnly );

		q_assert(stream.writeBytes(packet.constData(), packet.size()).status() == QDataStream::Ok);
		return writeBuffer(buffer);
	}
    else
    {
        HbWarning( "Try to write an empty packet." );
    }

	return 0;
}

bool HbAbstractSocket::packetAvailable() const
{
    return ( !_packets.isEmpty() );
}

QString HbAbstractSocket::errorString() const
{
    if( !_device )
    {
        return _device->errorString();
    }
    else
    {
        return QStringLiteral("");
    }
}

qint64 HbAbstractSocket::readStream( QDataStream & stream )
{
	qint64 bytesRead = 0;
    quint32 expected = sizeof(quint32);
    if( _bytesPending > 0 )
    {
        expected = _bytesPending;
    }

    while ( stream.device()->bytesAvailable() >= expected ) // Multi packets.
	{
        if ( _bytesPending == 0)
		{
            QDataStream::Status status = (stream >> _bytesPending).status();
            q_assert( status == QDataStream::Ok );

			expected = _bytesPending;
		}
        if ( expected > 0 )
		{
            if ( stream.device()->bytesAvailable() >= expected )
            {
                QByteArray buffer = stream.device()->read( expected );

				if (buffer.isEmpty())
				{
					bytesRead = -1;
				}
				else
				{
                    _packets.enqueue( buffer );
					bytesRead += expected;
				}

				_bytesPending = 0;
				expected = sizeof(quint32);
			}
		}

		if (bytesRead < 0)
		{
            HbWarning( "No bytes read => packets cleared." );
			stream.device()->readAll();
			_packets.clear();

			return bytesRead;
		}
	}

	if( _packets.size() > 0 )
	{
        emit socketReadyPacket();
	}

	return bytesRead;
}

qint64 HbAbstractSocket::writeBuffer(const QByteArray & buffer) const
{
    if( buffer.isEmpty())
    {
        HbWarning( "Try to write an empty buffer." );
        return 0;
    }

    return _device->write(buffer);
}
