// Qt
#include <QtCore/QTimer>
// Hb
#include <inputs/HbLogUdpSocketInput.h>
#include <HbLogMessage.h>

using namespace hb::log;


HbLogUdpSocketInput::HbLogUdpSocketInput( const QString & ip, quint32 port ) :
    QUdpSocket(), HbLogAbstractInput( HbLogAbstractInput::INPUT_UDP_SOCKET )
{
    mIp = ip;
    mPort = port;
    mExpected = 0;
    
    q_assert( connect( this, &QUdpSocket::readyRead, this,
        &HbLogUdpSocketInput::onReadyRead, Qt::UniqueConnection ) );

    q_assert( connect( this, ( void ( QUdpSocket::* )( QAbstractSocket::SocketError ) ) &QUdpSocket::error,
        this, [this]( QAbstractSocket::SocketError )
        {
            fprintf( stderr, "%s\n", HbLatin1( errorString() ) );

        }, Qt::UniqueConnection ) );

    onReconnection();
}

HbLogUdpSocketInput::~HbLogUdpSocketInput()
{

}

const QString & HbLogUdpSocketInput::ip() const
{
    return mIp;
}

quint32 HbLogUdpSocketInput::port() const
{
    return mPort;
}

void HbLogUdpSocketInput::onReconnection()
{
    if( !bind( QHostAddress( mIp ), mPort ) )
    {
        QTimer::singleShot( 5000, this, &HbLogUdpSocketInput::onReconnection );
    }
}

void HbLogUdpSocketInput::onReadyRead()
{
    do
    {
        QByteArray datagram( pendingDatagramSize(), 0 );
        readDatagram( datagram.data(), datagram.size() );
        QDataStream stream( datagram );
        stream >> mExpected;

        HbLogMessage * message = q_check_ptr( new HbLogMessage() );
        message->fromDataStream( stream );
        emit inputMessageReceived( message );
    }
    while( hasPendingDatagrams() );
}

