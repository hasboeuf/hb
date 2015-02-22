// Qt
#include <QtCore/QThread>
#include <QtCore/QSortFilterProxyModel>
#include <QtCore/QDebug>
#include <QtWidgets/QDateTimeEdit>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMessageBox>
#include <QtGui/QCloseEvent>
#include <QtGui/QStandardItemModel>
// Hb
#include <HbGlobal.h>
#include <HbLogService.h>
#include <gui/HbLogWidget.h>
#include <HbLoggerOutputs.h>
#include <HbServer.h>
// Local
#include <ServerMainWindow.h>
#include <ServerAuthStrategy.h>


using namespace hb::log;
using namespace hb::network;
using namespace hb::networkexample;

ServerMainWindow::ServerMainWindow(QWidget *parent) :
    QMainWindow(parent)
{

    // Log
    /*QString error;
    if( HbLogService::outputs()->addConsoleOutput( &error ) == 0 )
    {
        qDebug() << "HbLog error: " << error;
    }*/

    HbLogBegin();


    HbGeneralServerConfig config;
    config.setAppName("hb-network-example");
    config.setProtocolVersion( 1 );
    config.auth().setAuthMaxTries( 3 );
    config.auth().setAuthTimeout( 60 );
    config.presence().setKickAliveThreshold( 20 );
    config.presence().setWarningAliveThreshold( 10 );

    mpHbServer = new HbServer( config );

    // Ui
    setupUi(this);
    setWindowTitle("Server");

    connect(ui_qpb_start, &QPushButton::clicked, this, &ServerMainWindow::onStartClicked);
    connect(ui_qpb_stop,  &QPushButton::clicked, this, &ServerMainWindow::onStopClicked);

    HbLogEnd();
}

ServerMainWindow::~ServerMainWindow()
{
    HbLogBegin();

    HbLogEnd();
}

void ServerMainWindow::onStartClicked()
{
    HbLogBegin();

    HbTcpServerConfig config;
    config.setAddress(QHostAddress::Any);
    config.setPort( 4000 );
    config.setMaxUsersPerThread( 1 );

    quint16 server_uid = mpHbServer->joinTcpServer( config );
    if( server_uid > 0 )
    {
        HbInfo( "Server #%d started.", server_uid );
    }

    HbLogEnd();
}

void ServerMainWindow::onStopClicked()
{
    HbLogBegin();

    mpHbServer->leave();

    HbLogEnd();
}
