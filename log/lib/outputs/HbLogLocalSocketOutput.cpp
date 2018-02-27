// Qt
#include <QtCore/QTimer>
#include <QtNetwork/QLocalSocket>
// Local
#include <outputs/HbLogLocalSocketOutput.h>
#include <HbLogMessage.h>

using namespace hb::log;

HbLogLocalSocketOutput::HbLogLocalSocketOutput(const QString & name , QObject * parent ) :
    HbLogAbstractOutput( parent )
{
    mName = name;
}

HbLogLocalSocketOutput::~HbLogLocalSocketOutput()
{
    mLocalSocket->close();
}

const QString & HbLogLocalSocketOutput::name() const
{
    return mName;
}

void HbLogLocalSocketOutput::init()
{
    mLocalSocket.reset( new QLocalSocket() );

    connect( mLocalSocket.data(), &QLocalSocket::disconnected, this, &HbLogLocalSocketOutput::onDisconnected );

    onReconnection();
}

void HbLogLocalSocketOutput::processMessage( const HbLogMessage & message )
{
    if( mLocalSocket->state() == QLocalSocket::ConnectedState )
    {
        mLocalSocket->write( message.toByteArray() );
        mLocalSocket->flush();
    }
}

void HbLogLocalSocketOutput::onReconnection()
{
    if( mLocalSocket->state() != QLocalSocket::ConnectedState )
    {
        mLocalSocket->connectToServer( mName );
        
        if( !mLocalSocket->waitForConnected( 0 ) )
        {
            onDisconnected();
        }
    }
}

void HbLogLocalSocketOutput::onDisconnected()
{
    QTimer::singleShot( 5000, this, &HbLogLocalSocketOutput::onReconnection );
}
