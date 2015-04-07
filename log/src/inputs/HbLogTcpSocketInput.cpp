// Qt
#include <QtNetwork/QTcpSocket>
// Hb
#include <inputs/HbLogTcpSocketInput.h>
#include <HbLogMessage.h>

using namespace hb::log;


HbLogTcpSocketInput::HbLogTcpSocketInput( quint32 port ) :
    QTcpServer(), HbLogAbstractInput( INPUT_TCP_SOCKET )
{
    mAvailable = 0;

    if( !listen( QHostAddress::Any, mPort = port ) )
        fprintf( stderr, "HbLogTcpSocketInput: Unable to start the TCP server\n" );
}

HbLogTcpSocketInput::~HbLogTcpSocketInput()
{
    // onDisconnected() handles the rest.
    foreach( QTcpSocket * client, mClients.values() )
        q_assert_ptr( client )->close();

    mClients.clear();
}


quint32 HbLogTcpSocketInput::port() const
{
    return mPort;
}


void HbLogTcpSocketInput::incomingConnection( qint32 descriptor )
{
    QTcpSocket * client = q_check_ptr( new QTcpSocket( this ) );
    client->setSocketDescriptor( descriptor );

    q_assert( connect( client, &QTcpSocket::disconnected, this,
        &HbLogTcpSocketInput::onClientDisconnected, Qt::UniqueConnection ) );

    q_assert( connect( client, &QTcpSocket::readyRead, this,
        &HbLogTcpSocketInput::onReadyRead, Qt::UniqueConnection ) );

    mClients.insert( client );
}


void HbLogTcpSocketInput::onReadyRead()
{
    QTcpSocket * socket = q_dynamic_cast( QTcpSocket *, sender() );
    QDataStream stream( q_assert_ptr( socket ) );

    do
    {
        if( !mAvailable )
        {
            if( socket->bytesAvailable() < sizeof( qint32 ) )
                 return;

            stream >> mAvailable;
        }

        if( socket->bytesAvailable() < mAvailable )
            return;

        HbLogMessage * message = q_check_ptr( new HbLogMessage() );
        message->fromDataStream( stream );
        emit inputMessageReceived( message );

        mAvailable = 0;
    }

    while( socket->bytesAvailable() > 0 );
}

void HbLogTcpSocketInput::onClientDisconnected()
{
    QTcpSocket * socket = q_dynamic_cast( QTcpSocket *, sender() );

    mClients.remove( q_assert_ptr( socket ) );
    socket->deleteLater();
}
