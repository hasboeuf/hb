// Qt
#include <QtCore/QDataStream>
#include <QtCore/QIODevice>
// Hb
#include <HbLogService.h>
// Local
#include <HbAbstractSocket.h>
#include <contract/HbComHeader.h>

using namespace hb::com;
using namespace hb::tools;

HbAbstractSocket::HbAbstractSocket(QIODevice * device)
{
    q_assert_ptr( device );
    mDevice = device;

    connect( mDevice.data(), &QIODevice::readyRead, this, &HbAbstractSocket::onReadyRead, Qt::UniqueConnection );

    mBytesPending = 0;
    mPackets.clear();
}

HbAbstractSocket::~HbAbstractSocket()
{
    if ( !mDevice.isNull() )
    {
        mDevice.data()->disconnect(); // Disconnect all signals.
        mDevice.data()->close();
        mDevice.data()->deleteLater();
    }
}

bool HbAbstractSocket::sendContract( ShConstHbComContract contract )
{
    QByteArray buffer;
    QDataStream stream( &buffer, QIODevice::WriteOnly );

    stream << contract->header();
    if ( !contract->write( stream ) )
    {
        HbError( "Invalid contract format." );
    }
    else
    {
        qint64 bytesWritten = writePacket( buffer );

        if ( bytesWritten > 0 )
        {
            return true;
        }

        q_assert( bytesWritten );
    }

    q_assert( stream.status() == QDataStream::Ok );

    return false;
}

QByteArray HbAbstractSocket::readPacket()
{
    if( !mPackets.isEmpty() )
    {
        return mPackets.dequeue();
    }

    HbWarning( "Read an empty packet." );
    return QByteArray();
}

qint64 HbAbstractSocket::writePacket( const QByteArray & packet ) const
{
    if ( !packet.isEmpty() )
    {
        QByteArray buffer;
        QDataStream stream( &buffer, QIODevice::WriteOnly );

        q_assert( stream.writeBytes( packet.constData(), packet.size() ).status() == QDataStream::Ok );
        return writeBuffer( buffer );
    }
    else
    {
        HbWarning( "Try to write an empty packet." );
    }

    return 0;
}

bool HbAbstractSocket::packetAvailable() const
{
    return ( !mPackets.isEmpty() );
}

QString HbAbstractSocket::errorString() const
{
    if( !mDevice.isNull() )
    {
        return mDevice.data()->errorString();
    }
    else
    {
        return QStringLiteral("");
    }
}

qint64 HbAbstractSocket::readStream( QDataStream & stream )
{
    qint64 bytesRead = 0;
    quint32 expected = sizeof( quint32 );
    if( mBytesPending > 0 )
    {
        expected = mBytesPending;
    }

    while ( stream.device()->bytesAvailable() >= expected ) // Multi packets.
    {
        if ( mBytesPending == 0)
        {
            QDataStream::Status status = ( stream >> mBytesPending ).status();
            q_assert( status == QDataStream::Ok );

            expected = mBytesPending;
        }
        if ( expected > 0 )
        {
            if ( stream.device()->bytesAvailable() >= expected )
            {
                QByteArray buffer = stream.device()->read( expected );

                if ( buffer.isEmpty() )
                {
                    bytesRead = -1;
                }
                else
                {
                    mPackets.enqueue( buffer );
                    bytesRead += expected;
                }

                mBytesPending = 0;
                expected = sizeof( quint32 );
            }
        }

        if ( bytesRead < 0 )
        {
            HbWarning( "No bytes read => packets cleared." );
            stream.device()->readAll();
            mPackets.clear();

            return bytesRead;
        }
    }

    if( mPackets.size() > 0 )
    {
        emit socketReadyPacket();
    }

    return bytesRead;
}

qint64 HbAbstractSocket::writeBuffer( const QByteArray & buffer ) const
{
    q_assert( !mDevice.isNull() );

    if( buffer.isEmpty() )
    {
        HbWarning( "Try to write an empty buffer." );
        return 0;
    }

    return mDevice->write( buffer );
}
