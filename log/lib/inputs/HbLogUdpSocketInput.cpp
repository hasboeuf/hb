// Qt
#include <QtCore/QTimer>
#include <QtNetwork/QUdpSocket>
// Hb
#include <inputs/HbLogUdpSocketInput.h>
#include <HbLogMessage.h>

using namespace hb::log;


HbLogUdpSocketInput::HbLogUdpSocketInput( const QString & ip, quint32 port, QObject * parent ) :
    HbLogAbstractInput( parent )
{
    mIp = ip;
    mPort = port;
    mExpected = 0;
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

void HbLogUdpSocketInput::init()
{
    mUdpSocket.reset( new QUdpSocket() );
    connect( mUdpSocket.data(), &QUdpSocket::readyRead, this, &HbLogUdpSocketInput::onReadyRead );
    connect( mUdpSocket.data(), ( void ( QUdpSocket::* )( QAbstractSocket::SocketError ) ) &QUdpSocket::error,
             this, [this]( QAbstractSocket::SocketError ) {
            fprintf( stderr, "%s\n", HbLatin1( mUdpSocket->errorString() ) );
    } );

    onReconnection();
}

void HbLogUdpSocketInput::onReconnection()
{
    if( !mUdpSocket->bind( QHostAddress( mIp ), mPort ) )
    {
        QTimer::singleShot( 5000, this, &HbLogUdpSocketInput::onReconnection );
    }
}

void HbLogUdpSocketInput::onReadyRead()
{
    do
    {
        QByteArray datagram( mUdpSocket->pendingDatagramSize(), 0 );
        mUdpSocket->readDatagram( datagram.data(), datagram.size() );
        QDataStream stream( datagram );
        stream >> mExpected;

        HbLogMessage * message = new HbLogMessage();
        message->fromDataStream( stream );
        emit inputMessageReceived( message );
    }
    while( mUdpSocket->hasPendingDatagrams() );
}
