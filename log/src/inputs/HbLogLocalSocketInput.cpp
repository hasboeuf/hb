
// Qt
#include <QtNetwork/QLocalSocket>
// Local
#include <inputs/HbLogLocalSocketInput.h>
#include <HbLogMessage.h>
#include <HbLoggerStream.h>

using namespace hb::log;

HbLogLocalSocketInput::HbLogLocalSocketInput(const QString & name) :
    QLocalServer(), HbLogAbstractInput( INPUT_LOCAL_SOCKET )
{
	mAvailable = 0;

    setSocketOptions( QLocalServer::UserAccessOption );

	mName = name;
	if (mName.isEmpty())
	{
		mName = QString::fromLatin1(HbLoggerStream::DEFAULT_LOCAL_SERVER_NAME);
	}

    if( !listen( mName ) )
        fprintf( stderr, "HbLogLocalSocketInput: Unable to start the local server\n" );

    q_assert( connect( this, &QLocalServer::newConnection, this,
        &HbLogLocalSocketInput::incomingConnection, Qt::UniqueConnection ) );
}


void HbLogLocalSocketInput::incomingConnection()
{
    QLocalSocket * client = q_assert_ptr( nextPendingConnection() );
 
    q_assert( connect( client, &QLocalSocket::disconnected, this,
        &HbLogLocalSocketInput::onClientDisconnected, Qt::UniqueConnection ) );

    q_assert( connect( client, &QLocalSocket::readyRead, this,
        &HbLogLocalSocketInput::onReadyRead, Qt::UniqueConnection ) );

    mClients.insert( client );
}

void HbLogLocalSocketInput::onReadyRead()
{
    QLocalSocket * socket = q_dynamic_cast( QLocalSocket *, sender() );
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

void HbLogLocalSocketInput::onClientDisconnected()
{
    QLocalSocket * socket = q_dynamic_cast( QLocalSocket *, sender() );

    mClients.remove( q_assert_ptr( socket ) );
    socket->deleteLater();
}
