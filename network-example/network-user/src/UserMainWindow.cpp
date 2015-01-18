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
//#include <HbNetGlobal.h>
#include <HbLogService.h>
#include <gui/HbLogWidget.h>
#include <HbLoggerOutputs.h>
// Local
#include <UserMainWindow.h>


using namespace hb::log;
using namespace hb::network;
using namespace hb::networkexample;

UserMainWindow::UserMainWindow(QWidget *parent) :
    QMainWindow(parent)
{

    mpLogWidget = new HbLogWidget( this );
    mpLogWidget->hide();

    q_assert( HbLogService::outputs()->addGuiOutput( HbLogService::outputs()->unusedId(), mpLogWidget->logNotifier() ) ); // TODO Notifier must be handle by hblog ???

    HbLogBegin();

    // Ui
    setupUi( this );
    setWindowTitle( "User" );

    connect( &mTcpClient, &HbTcpClient::connected,    this, &UserMainWindow::onClientConnected );
    connect( &mTcpClient, &HbTcpClient::disconnected, this, &UserMainWindow::onClientDisconnected );

    // Internal connects
    connect( ui_qa_logs,   &QAction::triggered,   this, &UserMainWindow::showLogs );
    connect( ui_qpb_start, &QPushButton::clicked, this, &UserMainWindow::onStartClicked );
    connect( ui_qpb_stop, &QPushButton::clicked, this, &UserMainWindow::onStopClicked );

    HbLogEnd();
}

UserMainWindow::~UserMainWindow()
{
    HbLogBegin();

    if ( mpLogWidget ) delete mpLogWidget;

    HbLogEnd();
}

void UserMainWindow::init()
{
    HbLogBegin();
    HbLogEnd();
}


void UserMainWindow::showLogs( bool visible )
{
    mpLogWidget->setVisible( visible );
}

void UserMainWindow::onClientConnected()
{
    HbLogBegin();
    HbLogEnd();
}

void UserMainWindow::onClientDisconnected()
{
    HbLogBegin();
    HbLogEnd();
}

void UserMainWindow::onStartClicked()
{
    HbLogBegin();

    HbTcpConfig config;
    config.setAddress( QHostAddress::LocalHost );
    config.setPort( 4000 );

    HbNetworkConfig::Timeout timeout;
    timeout.connection    = 10;
    timeout.reconnection  = 2000;
    timeout.disconnection = 10;

    config.setTimeout( timeout );

    mTcpClient.setConfiguration( config );
    mTcpClient.join();


    HbLogEnd();
}

void UserMainWindow::onStopClicked()
{
    mTcpClient.leave();
}
