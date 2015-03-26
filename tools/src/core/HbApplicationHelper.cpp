// Qt
#include <QtWidgets/QApplication>
#include <QtWidgets/QStyleFactory>
#include <QtGui/QPalette>
#include <QtGui/QIcon>
#include <QtCore/QTime>
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
