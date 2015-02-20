// Qt
// Hb
#include <HbGlobal.h>
#include <HbLogService.h>
#include <gui/HbLogWidget.h>
#include <HbLoggerOutputs.h>
// Local
#include <ResponseContract.h>
#include <RequestContract.h>
#include <MessageContract.h>
#include <ComServerMainWindow.h>

using namespace hb::log;
using namespace hb::com;
using namespace hb::comexample;

ComServerMainWindow::ComServerMainWindow(QWidget *parent) :
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
    setWindowTitle( "ComServer" );

    HbComProtocol::msAppName         = "HbComExample";
    HbComProtocol::msProtocolVersion = 1;

    connect( ui_qpb_start,         &QPushButton::clicked, this, &ComServerMainWindow::onStartClicked);
    connect( ui_qpb_send_contract, &QPushButton::clicked, this, &ComServerMainWindow::onSendContractClicked );
    connect( ui_qpb_stop,          &QPushButton::clicked, this, &ComServerMainWindow::onStopClicked);

    connect( &mTcpServer, &HbTcpServer::serverConnected,        this, &ComServerMainWindow::onServerConnected );
    connect( &mTcpServer, &HbTcpServer::serverDisconnected,     this, &ComServerMainWindow::onServerDisconnected );
    connect( &mTcpServer, &HbTcpServer::socketConnected,        this, &ComServerMainWindow::onSocketConnected );
    connect( &mTcpServer, &HbTcpServer::socketDisconnected,     this, &ComServerMainWindow::onSocketDisconnected );
    connect( &mTcpServer, &HbTcpServer::socketContractReceived, this, &ComServerMainWindow::onSocketContractReceived );

    HbLogEnd();
}

ComServerMainWindow::~ComServerMainWindow()
{
    HbLogBegin();

    HbLogEnd();
}

void ComServerMainWindow::onStartClicked()
{
    HbLogBegin();

    HbTcpServerConfig config;
    config.setAddress(QHostAddress::Any);
    config.setPort( 4000 );
    config.setMaxUsersPerThread( 1 );

    mTcpServer.join( config );

    HbLogEnd();
}

void ComServerMainWindow::onSendContractClicked()
{
    HbLogBegin();

    HbLogEnd();
}

void ComServerMainWindow::onStopClicked()
{
    HbLogBegin();

    mTcpServer.leave();

    HbLogEnd();
}

void ComServerMainWindow::onServerConnected( servuid server_uid )
{
    HbLogBegin();
    HbLogEnd();
}

void ComServerMainWindow::onServerDisconnected( servuid server_uid )
{
    HbLogBegin();
    HbLogEnd();
}

void ComServerMainWindow::onSocketConnected( servuid server_uid, sockuid socket_uid )
{
    HbLogBegin();
    HbLogEnd();
}

void ComServerMainWindow::onSocketDisconnected( servuid server_uid, sockuid socket_uid )
{
    HbLogBegin();
    HbLogEnd();
}

void ComServerMainWindow::onSocketContractReceived( servuid server_uid, sockuid socket_uid, const HbComContract * contract )
{
    HbLogBegin();
    HbLogEnd();
}
