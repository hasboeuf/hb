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

void HbLogConsoleOutput::processMessage( const HbLogMessage & message )
{
    fprintf( stderr, "%s\n", HbLatin1( message.toString() ) );
}
