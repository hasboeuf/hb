// Qt
#include <QtCore/QUrl>
#include <QtGui/QDesktopServices>
#include <QtNetwork/QNetworkReply>
// Hb
#include <HbLogService.h>
#include <o2/HbO2Facebook.h>
#include <HbLinkConstant.h>
// Local
#include <LinkMainWindow.h>


using namespace hb::link;
using namespace hb::linkexample;

LinkMainWindow::LinkMainWindow(QWidget * parent) :
    QMainWindow( parent )
{

    HbLogBegin();

    // Ui
    setupUi( this );
    setWindowTitle( "Link" );

    mpO2 = nullptr;

    connect( ui_qpb_connect, &QPushButton::clicked, this, &LinkMainWindow::onConnectClicked );
    connect( &mNetworkAccess, &QNetworkAccessManager::finished, this, &LinkMainWindow::onNetworkAccessFinished );

    HbLogEnd();
}

LinkMainWindow::~LinkMainWindow()
{
    HbLogBegin();

    if( mpO2 )
    {
        delete mpO2;
    }

    HbLogEnd();
}

void LinkMainWindow::onConnectClicked()
{
    HbLogBegin();

    mpO2 = new HbO2Facebook();

    connect( mpO2, &HbO2::openBrowser, this, &LinkMainWindow::onOpenBrower );

    mpO2->setClientId( "940633959281250" );
    mpO2->setLocalPort( 8080 );
    mpO2->link();

    HbLogEnd();

}

void LinkMainWindow::onNetworkAccessFinished( QNetworkReply * reply )
{
    HbLogBegin();

    if( reply->error() == QNetworkReply::NoError )
    {
        HbInfo( "Reply succeed." );

        QByteArray raw = reply->readAll();
        QString content( raw );

        HbInfo( "Reply content: %s", HbLatin1( content ) );
    }
    else
    {
        HbError( "Reply error: %s", HbLatin1( reply->errorString() ) );
    }

    reply->deleteLater();

    HbLogEnd();
}

void LinkMainWindow::onOpenBrower( const QUrl & url )
{
    HbInfo( "Opening browser on %s", HbLatin1( url.toString() ) );
    QDesktopServices::openUrl( url );
}
