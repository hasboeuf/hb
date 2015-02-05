// Qt
#include <QtCore/QCoreApplication>
#include <QtCore/QDebug>
// Hb
#include <o2/HbO2Facebook.h>
// Local


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    HbO2Facebook auth;

	return a.exec();
}
