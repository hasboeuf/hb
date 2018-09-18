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
    qDebug() << "Opening browser on" << url.toString();
    QDesktopServices::openUrl( url );
}

void LinkBrowserControls::onCloseBrowser()
{
    qDebug() << "Browser could be closed";
}
