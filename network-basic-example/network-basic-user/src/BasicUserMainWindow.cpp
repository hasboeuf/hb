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
#include <BasicUserMainWindow.h>

using namespace hb::tools;
using namespace hb::log;
using namespace hb::network;
using namespace hb::networkexample;

BasicUserMainWindow::BasicUserMainWindow(QWidget *parent) :
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
    setWindowTitle( "BasicUser" );

    HbNetworkProtocol::msAppName         = "HbBasicNetworkExample";
    HbNetworkProtocol::msProtocolVersion = 1;

    connect( ui_qpb_start,         &QPushButton::clicked, this, &BasicUserMainWindow::onStartClicked );
    connect( ui_qpb_send_contract, &QPushButton::clicked, this, &BasicUserMainWindow::onSendContractClicked );
    connect( ui_qpb_stop,          &QPushButton::clicked, this, &BasicUserMainWindow::onStopClicked );

    connect( &mTcpClient, &HbTcpClient::clientConnected,        this, &BasicUserMainWindow::onClientConnected );
    connect( &mTcpClient, &HbTcpClient::clientDisconnected,     this, &BasicUserMainWindow::onClientDisconnected );
    connect( &mTcpClient, &HbTcpClient::clientContractReceived, this, &BasicUserMainWindow::onClientContractReceived );

    HbLogEnd();
}

void BasicUserMainWindow::onStartClicked()
{
    HbLogBegin();

    HbTcpClientConfig config;
    config.setAddress( QHostAddress::LocalHost );
    config.setPort( 4001 );
    config.setReconnectionDelay( 1000 );

    config.exchanges().plug< RequestContract  >();
    config.exchanges().plug< ResponseContract >();
    config.exchanges().plug< MessageContract  >();

    mTcpClient.join( config );

    HbLogEnd();
}

void BasicUserMainWindow::onSendContractClicked()
{
    HbInfo( "Send request contract." );

    RequestContract * request = new RequestContract();
    request->setRequest( "What ever im asking, ill get the same response." );

    mTcpClient.send( ShConstHbNetworkContract( request ) );
}

void BasicUserMainWindow::onStopClicked()
{
    mTcpClient.leave();
}

void BasicUserMainWindow::onClientConnected( networkuid client_uid )
{
    HbInfo( "Client %d connected.", client_uid );
}

void BasicUserMainWindow::onClientDisconnected( networkuid client_uid )
{
    HbInfo( "Client %d disconnected.", client_uid );
}

void BasicUserMainWindow::onClientContractReceived( networkuid client_uid, const HbNetworkContract * contract )
{
    q_assert_ptr( contract );

    HbInfo( "Contract received on client %d.", client_uid );
    HbInfo( "Contract details: %s", HbLatin1( contract->toString() ) );

    const ResponseContract * response = contract->value< ResponseContract >();
    if( response )
    {
        HbInfo( "Contract is of type ResponseContract." );
    }

    const MessageContract * message = contract->value< MessageContract >();
    if( message )
    {
        HbInfo( "Contract is of type MessageContract." );
    }

    delete contract;
}
