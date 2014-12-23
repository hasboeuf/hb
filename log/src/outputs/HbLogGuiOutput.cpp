// Hb
#include <outputs/HbLogGuiOutput.h>
#include <HbLogGuiNotifier.h>

using namespace hb::log;


HbLogGuiOutput::HbLogGuiOutput( HbLogGuiNotifier * notifier, HbLogger::Levels level ) :
    HbLogAbstractOutput( HbLogAbstractOutput::OUTPUT_GUI, level )
{
	mpNotifier = notifier;
}

HbLogGuiOutput::~HbLogGuiOutput()
{
	delete mpNotifier;
	mpNotifier = nullptr;
}


void HbLogGuiOutput::processMessage( const HbLogMessage & message )
{
	if( mpNotifier )
		q_assert( QMetaObject::invokeMethod( mpNotifier, "onNewLogMessage", Q_ARG( HbLogMessage, message ) ) );
}
