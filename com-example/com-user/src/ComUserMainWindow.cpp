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
#include <ComUserMainWindow.h>

using namespace hb::tools;
using namespace hb::log;
using namespace hb::com;
using namespace hb::comexample;

ComUserMainWindow::ComUserMainWindow(QWidget *parent) :
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
    setWindowTitle( "ComUser" );

    HbComProtocol::msAppName         = "HbComExample";
    HbComProtocol::msProtocolVersion = 1;

    connect( ui_qpb_start,         &QPushButton::clicked, this, &ComUserMainWindow::onStartClicked );
    connect( ui_qpb_send_contract, &QPushButton::clicked, this, &ComUserMainWindow::onSendContractClicked );
    connect( ui_qpb_stop,          &QPushButton::clicked, this, &ComUserMainWindow::onStopClicked );

    connect( &mTcpClient, &HbTcpClient::clientConnected,        this, &ComUserMainWindow::onClientConnected );
    connect( &mTcpClient, &HbTcpClient::clientDisconnected,     this, &ComUserMainWindow::onClientDisconnected );
    connect( &mTcpClient, &HbTcpClient::clientContractReceived, this, &ComUserMainWindow::onClientContractReceived );

    HbLogEnd();
}

void ComUserMainWindow::onStartClicked()
{
    HbLogBegin();

    HbTcpClientConfig config;
    config.setAddress( QHostAddress::LocalHost );
    config.setPort( 4001 );
    config.setReconnectionDelay( 1000 );

    config.exchanges().plug< RequestContract >();
    config.exchanges().plug< ResponseContract >();
    config.exchanges().plug< MessageContract >();

    mTcpClient.join( config );

    HbLogEnd();
}

void ComUserMainWindow::onSendContractClicked()
{
    HbInfo( "Send request contract." );

    RequestContract * request = new RequestContract();
    request->setRequest( "What ever im asking, ill get the same response." );

    mTcpClient.send( ShConstHbComContract( request ) );
}

void ComUserMainWindow::onStopClicked()
{
    mTcpClient.leave();
}

void ComUserMainWindow::onClientConnected( sockuid client_uid )
{
    HbInfo( "Client %d connected.", client_uid );
}

void ComUserMainWindow::onClientDisconnected( sockuid client_uid )
{
    HbInfo( "Client %d disconnected.", client_uid );
}

void ComUserMainWindow::onClientContractReceived( sockuid client_uid, const HbComContract * contract )
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
