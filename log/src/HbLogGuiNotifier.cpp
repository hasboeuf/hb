// Hb
#include <HbLogGuiNotifier.h>

using namespace hb::log;


HbLogGuiNotifier::HbLogGuiNotifier() : 
    QObject()
{
}


void HbLogGuiNotifier::onNewLogMessage( const HbLogMessage & message )
{
	emit newLogMessage( message );
}

