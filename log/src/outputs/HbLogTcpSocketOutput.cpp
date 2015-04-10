// Qt
#include <QtCore/QTimer>
// Hb
#include <outputs/HbLogTcpSocketOutput.h>
#include <HbLogMessage.h>

using namespace hb::log;


HbLogTcpSocketOutput::HbLogTcpSocketOutput( const QString & ip, quint32 port, HbLogger::Levels level ) :
    QTcpSocket(), HbLogAbstractOutput( HbLogAbstractOutput::OUTPUT_TCP_SOCKET, level )
{
    mIp = ip;
    mPort = port;
    
    q_assert( connect( this, &QTcpSocket::disconnected, this,
        &HbLogTcpSocketOutput::onDisconnected, Qt::UniqueConnection ) );

    q_assert( connect( this, ( void ( QTcpSocket::* )( QAbstractSocket::SocketError ) ) &QTcpSocket::error,
        this, [this]( QAbstractSocket::SocketError )
        {
            fprintf(stderr, "%s\n", HbLatin1(errorString()));

        }, Qt::UniqueConnection ) );

    onReconnection();
}

HbLogTcpSocketOutput::~HbLogTcpSocketOutput()
{
    close();
}


bool HbLogTcpSocketOutput::isValid() const
{
    return ( state() == QAbstractSocket::ConnectedState );
}


const QString & HbLogTcpSocketOutput::ip() const
{
    return mIp;
}

quint32 HbLogTcpSocketOutput::port() const
{
    return mPort;
}


void HbLogTcpSocketOutput::processMessage( const HbLogMessage & message )
{
    if( state() == QAbstractSocket::ConnectedState )
    {
        write( message.toByteArray() );
        flush();
    }
}


void HbLogTcpSocketOutput::onReconnection()
{
    if( state() != QAbstractSocket::ConnectedState )
    {
        connectToHost( mIp, mPort );
    }
}

void HbLogTcpSocketOutput::onDisconnected()
{
    QTimer::singleShot( 5000, this, SLOT( onReconnection() ) );
}
