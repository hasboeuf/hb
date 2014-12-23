// Qt
#include <QtCore/QTimer>
// Local
#include <outputs/HbLogLocalSocketOutput.h>
#include <HbLogMessage.h>
#include <HbLoggerStream.h>

using namespace hb::log;

HbLogLocalSocketOutput::HbLogLocalSocketOutput( const QString & name, HbLogger::Levels level ) :
    QLocalSocket(), HbLogAbstractOutput( HbLogAbstractOutput::OUTPUT_LOCAL_SOCKET, level )
{
	mName = name;
	if (mName.isEmpty())
	{
		mName = QString::fromLatin1(HbLoggerStream::DEFAULT_LOCAL_SERVER_NAME);
	}

    q_assert( connect( this, &QLocalSocket::disconnected, this,
        &HbLogLocalSocketOutput::onDisconnected, Qt::UniqueConnection ) );

	onReconnection();
}

HbLogLocalSocketOutput::~HbLogLocalSocketOutput()
{
	close();
}


bool HbLogLocalSocketOutput::isValid() const
{
    return ( state() == QLocalSocket::ConnectedState );
}


void HbLogLocalSocketOutput::processMessage( const HbLogMessage & message )
{
	if( state() == QLocalSocket::ConnectedState )
	{
        write( message.toByteArray() );
        flush();
	}
}


void HbLogLocalSocketOutput::onReconnection()
{
    if( state() != QLocalSocket::ConnectedState )
    {
        connectToServer( mName );
        
        if( !waitForConnected( 0 ) )
            onDisconnected();
    }
}

void HbLogLocalSocketOutput::onDisconnected()
{
    QTimer::singleShot( 1000, this, SLOT( onReconnection() ) );
}
