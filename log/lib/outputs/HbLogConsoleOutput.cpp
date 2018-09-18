// Hb
#include <outputs/HbLogConsoleOutput.h>
#include <HbLogMessage.h>

using namespace hb::log;


HbLogConsoleOutput::HbLogConsoleOutput( QObject * parent ) :
    HbLogAbstractOutput( parent )
{
}

void HbLogConsoleOutput::init()
{

}

void HbLogConsoleOutput::processMessage( const HbLogMessagePtr & message )
{
    fprintf( stderr, "%s\n", qUtf8Printable( message->toString() ) );
}
