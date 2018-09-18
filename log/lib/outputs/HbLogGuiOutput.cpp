// Hb
#include <outputs/HbLogGuiOutput.h>
#include <HbLogGuiNotifier.h>

using namespace hb::log;


HbLogGuiOutput::HbLogGuiOutput( HbLogGuiNotifier * notifier , QObject * parent) :
    HbLogAbstractOutput( parent )
{
    mNotifier.reset( notifier );
}

HbLogGuiOutput::~HbLogGuiOutput()
{
    mNotifier.take()->deleteLater(); // mNotifier does not leave in the same thread.
}

void HbLogGuiOutput::init()
{

}

void HbLogGuiOutput::processMessage( const HbLogMessagePtr & message )
{
    if( mNotifier ) {
        QMetaObject::invokeMethod( mNotifier.data(), [this, message]() {
            mNotifier->newLogMessage( message );
        } );
    }
}
