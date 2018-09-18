// Qt
#include <QtNetwork/QTcpServer>
#include <QtNetwork/QTcpSocket>
// Hb
#include <inputs/HbLogTcpSocketInput.h>
#include <HbLogMessage.h>

using namespace hb::log;


HbLogTcpSocketInput::HbLogTcpSocketInput( quint16 port, QObject * parent ) :
    HbLogAbstractInput( parent )
{
    mExpected = 0;
    mPort = port;
}

HbLogTcpSocketInput::~HbLogTcpSocketInput()
{
    // onDisconnected() handles the rest.
    for( QTcpSocket * client: mClients.values() ) {
        q_assert_ptr( client )->close();
    }

    mClients.clear();
}


quint16 HbLogTcpSocketInput::port() const
{
    return mPort;
}

void HbLogTcpSocketInput::init()
{
    mTcpServer.reset( new QTcpServer() );
    connect(mTcpServer.data(), &QTcpServer::newConnection, this, &HbLogTcpSocketInput::onNewConnection);
    if( !mTcpServer->listen( QHostAddress::Any, mPort ) )
    {
        std::cerr << "HbLog: tcp input failed to start on port " << mPort << std::endl;
    }
}

void HbLogTcpSocketInput::onNewConnection()
{
    QTcpSocket * client = mTcpServer->nextPendingConnection();
    Q_ASSERT(client);

    connect( client, &QTcpSocket::disconnected, this, &HbLogTcpSocketInput::onClientDisconnected );
    connect( client, &QTcpSocket::readyRead, this, &HbLogTcpSocketInput::onReadyRead );

    mClients.insert( client );
}

void HbLogTcpSocketInput::onReadyRead()
{
    QTcpSocket * socket = q_dynamic_cast( QTcpSocket *, sender() );
    QDataStream stream( socket );

    do
    {
        if( !mExpected )
        {
            if( socket->bytesAvailable() < sizeof( qint32 ) )
                 return;

            stream >> mExpected;
        }

        if( socket->bytesAvailable() < mExpected )
            return;

        HbLogMessage * message = new HbLogMessage();
        message->fromDataStream( stream );
        emit inputMessageReceived( message );

        mExpected = 0;
    }
    while( socket->bytesAvailable() > 0 );
}

void HbLogTcpSocketInput::onClientDisconnected()
{
    QTcpSocket * socket = q_dynamic_cast( QTcpSocket *, sender() );

    mClients.remove( socket );
    socket->deleteLater();
}
