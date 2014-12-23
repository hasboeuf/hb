// Hb
#include <outputs/HbLogConsoleOutput.h>
#include <HbLogMessage.h>

using namespace hb::log;


HbLogConsoleOutput::HbLogConsoleOutput( HbLogger::Levels level ) :
    HbLogAbstractOutput( HbLogAbstractOutput::OUTPUT_CONSOLE, level )
{
}


void HbLogConsoleOutput::processMessage( const HbLogMessage & message )
{
    fprintf( stderr, "%s\n", HbLatin1( message.toString() ) );
}
