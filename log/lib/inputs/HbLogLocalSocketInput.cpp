// Qt
#include <QtNetwork/QLocalServer>
#include <QtNetwork/QLocalSocket>
#include <QThread>
// Local
#include <inputs/HbLogLocalSocketInput.h>
#include <HbLogMessage.h>

using namespace hb::log;

HbLogLocalSocketInput::HbLogLocalSocketInput( const QString & name, QObject * parent ) :
    HbLogAbstractInput( parent )
{
    mExpected = 0;
    mName = name;
}

HbLogLocalSocketInput::~HbLogLocalSocketInput()
{
    qDeleteAll( mClients );
}

const QString & HbLogLocalSocketInput::name() const
{
    return mName;
}

void HbLogLocalSocketInput::init()
{
    mLocalServer.reset( new QLocalServer() );
    mLocalServer->setSocketOptions( QLocalServer::UserAccessOption );

    if( !mLocalServer->listen( mName ) ) {
        std::cerr << "HbLog: local input failed to start on " << qUtf8Printable(mName) << std::endl;
    }

    connect( mLocalServer.data(), &QLocalServer::newConnection, this, &HbLogLocalSocketInput::incomingConnection );
}

void HbLogLocalSocketInput::incomingConnection()
{
    QLocalSocket * client = mLocalServer->nextPendingConnection();

    connect( client, &QLocalSocket::disconnected, this, &HbLogLocalSocketInput::onClientDisconnected );
    connect( client, &QLocalSocket::readyRead, this, &HbLogLocalSocketInput::onReadyRead );

    mClients.insert( client );
}

void HbLogLocalSocketInput::onReadyRead()
{
    QLocalSocket * socket = q_dynamic_cast( QLocalSocket *, sender() );
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

        HbLogMessage * message = q_check_ptr( new HbLogMessage() );
        message->fromDataStream( stream );
        emit inputMessageReceived( message );

        mExpected = 0;
    }

    while( socket->bytesAvailable() > 0 );
}

void HbLogLocalSocketInput::onClientDisconnected()
{
    QLocalSocket * socket = q_dynamic_cast( QLocalSocket *, sender() );

    mClients.remove( q_assert_ptr( socket ) );
    socket->deleteLater();
}
