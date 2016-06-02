// Qt
#include <QtGui/QDesktopServices>
#include <QtCore/QUrl>
// Hb
#include <HbLogService.h>
// Local
#include <LinkBrowserControls.h>

using namespace hb::linkexample;

void LinkBrowserControls::onOpenBrowser( const QUrl & url )
{
    HbInfo( "Opening browser on %s", HbLatin1( url.toString() ) );
    QDesktopServices::openUrl( url );
}

void LinkBrowserControls::onCloseBrowser()
{
    HbInfo( "Browser could be closed." );
}
