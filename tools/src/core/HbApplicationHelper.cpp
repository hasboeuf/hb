// Qt
#include <QtCore/QCoreApplication>
#include <QtCore/QThread>
#include <QtWidgets/QApplication>
#include <QtWidgets/QStyleFactory>
#include <QtGui/QPalette>
#include <QtGui/QIcon>
#include <QtCore/QTime>
#include <QtCore/QSet>
#include <QtCore/QDebug>
// System
#if defined Q_OS_WIN32
#include <Windows.h>
#elif defined Q_OS_LINUX || defined Q_OS_DARWIN
#include "unistd.h"
#include <signal.h>
#endif
// Local
#include <core/HbApplicationHelper.h>

using namespace hb::tools;

void HbApplicationHelper::initApp(const QString & company, const QString & domain, const QString & name)
{
    // New seed for the app
    QTime time = QTime::currentTime();
    qsrand( ( uint ) time.msec() );

    QCoreApplication* app = QCoreApplication::instance();
    if (!app)
    {
        return;
    }

    // QSettings
    QCoreApplication::setOrganizationName( company );
    QCoreApplication::setOrganizationDomain( domain );
    if (!name.isEmpty()) QCoreApplication::setApplicationName( name );
}

void HbApplicationHelper::initSkin( const QString & skin )
{
    // Logo
    QApplication::setWindowIcon( QIcon( ":/HbLogo.png" ) );

    // Style
    qApp->setStyle(QStyleFactory::create(skin));
    QPalette p;
    p = qApp->palette();
    p.setColor(QPalette::Window, QColor(89, 89, 89));
    p.setColor(QPalette::WindowText, QColor(198, 198, 198));
    p.setColor(QPalette::Base, QColor(166, 166, 166));
    //p.setColor(QPalette::Text, QColor(255,255,255));
    p.setColor(QPalette::AlternateBase, QColor(153, 204, 153));
    //p.setColor(QPalette::ToolTipBase, QColor(255,255,255));
    //p.setColor(QPalette::ToolTipText, QColor(255,255,255));
    p.setColor(QPalette::Button, QColor(53, 53, 53));
    p.setColor(QPalette::ButtonText, QColor(255, 255, 255));
    p.setColor(QPalette::Highlight, QColor(102, 204, 51));
    //p.setColor(QPalette::HighlightedText, QColor(255,255,255));
    //p.setColor(QPalette::Link, QColor(255,255,255));
    //p.setColor(QPalette::LinkVisited, QColor(255,255,255));

    qApp->setPalette(p);

}

void HbApplicationHelper::catchInterruptingEvents()
{
#if defined Q_OS_WIN32
    auto handler = []( DWORD sig ) -> BOOL {
        switch( sig )
        {
        case CTRL_C_EVENT:
        case CTRL_CLOSE_EVENT:
        case CTRL_BREAK_EVENT:
        case CTRL_LOGOFF_EVENT:
        case CTRL_SHUTDOWN_EVENT:
            // This callback is called from another thread than Qt main thread.
            // That is why we wait for Qt main thread to finish.

            qCritical() << QString( "Signal %1 caught. Quit qApp." ).arg( sig );
            QMetaObject::invokeMethod( qApp, "quit", Qt::QueuedConnection );
            qApp->thread()->wait();
        default:
            break;
        }

        return FALSE;
    };

    SetConsoleCtrlHandler( handler, TRUE );

#elif defined Q_OS_LINUX || defined Q_OS_DARWIN

    auto handler = []( int sig ) {
        qCritical() << QString( "Signal %1 caught. Quit qApp." ).arg( sig );
        qApp->quit();
    };

    QSet< int > sigs = {SIGQUIT, SIGINT, SIGTERM, SIGHUP};
    for( int sig : sigs )
    {
        signal( sig, handler );
    }

#endif
}
