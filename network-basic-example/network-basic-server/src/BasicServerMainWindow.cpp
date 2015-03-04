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
#include <BasicServerMainWindow.h>

using namespace hb::log;
using namespace hb::network;
using namespace hb::networkexample;

BasicServerMainWindow::BasicServerMainWindow(QWidget *parent) :
    QMainWindow( parent )
{

    // Log
    /*QString error;
    if( HbLogService::outputs()->addConsoleOutput( &error ) == 0 )
    {
        printf( "HbLog error: %s", HbLatin1( error ) );
    }*/


    HbLogBegin();

    // Ui
    setupUi( this );
    setWindowTitle( "BasicServer" );

    HbNetworkProtocol::msAppName         = "HbBasicNetworkExample";
    HbNetworkProtocol::msProtocolVersion = 1;

    connect( ui_qpb_start,         &QPushButton::clicked, this, &BasicServerMainWindow::onStartClicked);
    connect( ui_qpb_send_contract, &QPushButton::clicked, this, &BasicServerMainWindow::onSendContractClicked );
    connect( ui_qpb_stop,          &QPushButton::clicked, this, &BasicServerMainWindow::onStopClicked);

    connect( &mTcpServer, &HbTcpServer::serverConnected,        this, &BasicServerMainWindow::onServerConnected );
    connect( &mTcpServer, &HbTcpServer::serverDisconnected,     this, &BasicServerMainWindow::onServerDisconnected );
    connect( &mTcpServer, &HbTcpServer::socketConnected,        this, &BasicServerMainWindow::onSocketConnected );
    connect( &mTcpServer, &HbTcpServer::socketDisconnected,     this, &BasicServerMainWindow::onSocketDisconnected );
    connect( &mTcpServer, &HbTcpServer::socketContractReceived, this, &BasicServerMainWindow::onSocketContractReceived );

    HbLogEnd();
}

void BasicServerMainWindow::onStartClicked()
{
    HbLogBegin();

    HbTcpServerConfig config;
    config.setAddress(QHostAddress::Any);
    config.setPort( 4001 );
    config.setMaxUsersPerThread( 1 );
    config.setBadHeaderTolerant( false );

    config.exchanges().plug< RequestContract  >();
    config.exchanges().plug< ResponseContract >();
    config.exchanges().plug< MessageContract  >();

    mTcpServer.join( config );

    HbLogEnd();
}

void BasicServerMainWindow::onSendContractClicked()
{
    HbInfo( "Send message contract to all sockets." );

    MessageContract * message = new MessageContract();
    message->setMessage( "Hello world" );
    message->setRouting( HbNetworkProtocol::ROUTING_BROADCAST ); // To all users.

    mTcpServer.send( ShConstHbNetworkContract( message ) );
}

void BasicServerMainWindow::onStopClicked()
{
    mTcpServer.leave();
}

void BasicServerMainWindow::onServerConnected( networkuid server_uid )
{
    HbInfo( "Server %d connected.", server_uid );
}

void BasicServerMainWindow::onServerDisconnected( networkuid server_uid )
{
    HbInfo( "Server %d disconnected.", server_uid );
}

void BasicServerMainWindow::onSocketConnected( networkuid server_uid, networkuid socket_uid )
{
    HbInfo( "Socket %d connected on server %d.", socket_uid, server_uid );
}

void BasicServerMainWindow::onSocketDisconnected( networkuid server_uid, networkuid socket_uid )
{
    HbInfo( "Socket %d disconnected on server %d.", socket_uid, server_uid );
}

void BasicServerMainWindow::onSocketContractReceived( networkuid server_uid, networkuid socket_uid, const HbNetworkContract * contract )
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
            mTcpServer.send( ShConstHbNetworkContract( response ) );
        }
    }

    delete contract;
}
