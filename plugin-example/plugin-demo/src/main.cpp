// Qt
#include <QtCore/QDebug>
#include <QtWidgets/QApplication>
// Local
#include <AppMainWindow.h>

using hb::pluginexample::AppMainWindow;

int main(int argc, char *argv[])
{
    QApplication a( argc, argv );

    QString plugin_dir;
    if( argc > 1 )
    {
        plugin_dir = QString::fromLatin1( argv[1] );
    }

    if( plugin_dir.isEmpty() )
    {
        plugin_dir = QCoreApplication::applicationDirPath() + "/plugins";
    }

    qDebug() << plugin_dir;

    AppMainWindow w( plugin_dir );
    w.show();
    
    return a.exec();
}
