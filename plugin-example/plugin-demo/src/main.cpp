#include "AppMainWindow.hpp"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    AppMainWindow w;
    w.show();
    
    return a.exec();
}
