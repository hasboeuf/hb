// Qt
#include <QtCore/QTimer>
#include <QtNetwork/QTcpSocket>
// Hb
#include <outputs/HbLogTcpSocketOutput.h>
#include <HbLogMessage.h>

using namespace hb::log;


HbLogTcpSocketOutput::HbLogTcpSocketOutput( const QString & ip, quint32 port, QObject * parent ) :
    HbLogAbstractOutput( parent )
{
    mIp = ip;
    mPort = port;
}

HbLogTcpSocketOutput::~HbLogTcpSocketOutput()
{
    mTcpSocket->close();
}

const QString & HbLogTcpSocketOutput::ip() const
{
    return mIp;
}

quint32 HbLogTcpSocketOutput::port() const
{
    return mPort;
}

void HbLogTcpSocketOutput::init()
{
    mTcpSocket.reset( new QTcpSocket() );

    connect( mTcpSocket.data(), &QTcpSocket::disconnected, this, &HbLogTcpSocketOutput::onDisconnected );

    connect( mTcpSocket.data(), ( void ( QTcpSocket::* )( QAbstractSocket::SocketError ) ) &QTcpSocket::error,
             this, [this]( QAbstractSocket::SocketError ) {
        fprintf(stderr, "%s\n", HbLatin1( mTcpSocket->errorString()));
    } );

    onReconnection();
}

void HbLogTcpSocketOutput::processMessage( const HbLogMessage & message )
{
    if( mTcpSocket->state() == QAbstractSocket::ConnectedState )
    {
        mTcpSocket->write( message.toByteArray() );
        mTcpSocket->flush();
    }
}

void HbLogTcpSocketOutput::onReconnection()
{
    if( mTcpSocket->state() == QAbstractSocket::UnconnectedState )
    {
        mTcpSocket->connectToHost( mIp, mPort );
    }
}

void HbLogTcpSocketOutput::onDisconnected()
{
    QTimer::singleShot( 5000, this, &HbLogTcpSocketOutput::onReconnection );
}
