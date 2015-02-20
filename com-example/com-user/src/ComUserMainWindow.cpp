// Qt
// Hb
#include <HbGlobal.h>
#include <HbLogService.h>
#include <gui/HbLogWidget.h>
#include <HbLoggerOutputs.h>
// Local
#include <ComUserMainWindow.h>

using namespace hb::tools;
using namespace hb::log;
using namespace hb::com;
using namespace hb::comexample;

ComUserMainWindow::ComUserMainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    // Log
    QString error;
    if( HbLogService::outputs()->addConsoleOutput( &error ) == 0 )
    {
        qDebug() << "HbLog error: " << error;
    }

    HbLogBegin();

    // Ui
    setupUi( this );
    setWindowTitle( "ComUser" );


    connect( ui_qpb_start, &QPushButton::clicked, this, &ComUserMainWindow::onStartClicked );
    connect( ui_qpb_stop,  &QPushButton::clicked, this, &ComUserMainWindow::onStopClicked );

    HbLogEnd();
}

ComUserMainWindow::~ComUserMainWindow()
{
    HbLogBegin();

    HbLogEnd();
}

void ComUserMainWindow::onClientConnected()
{
    HbLogBegin();
    HbLogEnd();
}

void ComUserMainWindow::onClientDisconnected()
{
    HbLogBegin();
    HbLogEnd();
}

void ComUserMainWindow::onStartClicked()
{
    HbLogBegin();



    HbLogEnd();
}

void ComUserMainWindow::onStopClicked()
{

}
