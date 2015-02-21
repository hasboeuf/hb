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
    /*QString error;
    if( HbLogService::outputs()->addConsoleOutput( &error ) == 0 )
    {
        qDebug() << "HbLog error: " << error;
    }*/


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

void ComServerMainWindow::onStartClicked()
{
    HbLogBegin();

    HbTcpServerConfig config;
    config.setAddress(QHostAddress::Any);
    config.setPort( 4001 );
    config.setMaxUsersPerThread( 1 );

    config.exchanges().plug< RequestContract  >();
    config.exchanges().plug< ResponseContract >();
    config.exchanges().plug< MessageContract  >();

    mTcpServer.join( config );

    HbLogEnd();
}

void ComServerMainWindow::onSendContractClicked()
{
    HbInfo( "Send message contract to all sockets." );

    MessageContract * message = new MessageContract();
    message->setMessage( "Hello world" );
    message->setRouting( HbComProtocol::BROADCAST ); // To all users.

    mTcpServer.send( ShConstHbComContract( message ) );
}

void ComServerMainWindow::onStopClicked()
{
    mTcpServer.leave();
}

void ComServerMainWindow::onServerConnected( servuid server_uid )
{
    HbInfo( "Server %d connected.", server_uid );
}

void ComServerMainWindow::onServerDisconnected( servuid server_uid )
{
    HbInfo( "Server %d disconnected.", server_uid );
}

void ComServerMainWindow::onSocketConnected( servuid server_uid, sockuid socket_uid )
{
    HbInfo( "Socket %d connected on server %d.", socket_uid, server_uid );
}

void ComServerMainWindow::onSocketDisconnected( servuid server_uid, sockuid socket_uid )
{
    HbInfo( "Socket %d disconnected on server %d.", socket_uid, server_uid );
}

void ComServerMainWindow::onSocketContractReceived( servuid server_uid, sockuid socket_uid, const HbComContract * contract )
{
    q_assert_ptr( contract );

    HbInfo( "Contract received from socket %d on server %d.", socket_uid, server_uid );
    HbInfo( "Contract details: %s", HbLatin1( contract->toString() ) );

    const RequestContract * request = contract->value< RequestContract >();
    if( request )
    {
        ResponseContract * response = request->reply();

        if( response )
        {
            response->setResponse( "Universal response." );
            mTcpServer.send( ShConstHbComContract( response ) );
        }
    }

    delete contract;
}
