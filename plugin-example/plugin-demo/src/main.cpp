// Qt
#include <QtWidgets/QApplication>
// Local
#include <AppMainWindow.h>

using hb::pluginexample::AppMainWindow;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    AppMainWindow w;
    w.show();
    
    return a.exec();
}
