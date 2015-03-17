// Qt
// Hb
#include <HbLogService.h>
#include <HbLoggerOutputs.h>
// Local
#include <ToolsMainWindow.h>

using namespace hb::tools;
using namespace hb::log;
using namespace hb::toolsexample;

ToolsMainWindow::ToolsMainWindow( QWidget * parent ) :
    QMainWindow( parent )
{

    // Log
    QString error;
    if( HbLogService::outputs()->addGuiOutput( ui_qw_log->logNotifier() ) )
    {
        printf( "HbLog error: %s", HbLatin1( error ) );
    }

    HbLogBegin();

    // Ui
    setupUi( this );
    setWindowTitle( "Tools" );

    testApplicationHelper();
    testDictionnaryHelper();
    testEnum();
    testErrorCode();
    testMultipleSortFilterProxyModel();
    testNullable();
    testSingleton();
    testSteadyDateTime();
    testUid();
    testUidGenerator();
    testHttpRequester();
    testTimeoutNetworkReplies();

    HbLogEnd();
}

ToolsMainWindow::~ToolsMainWindow()
{
    HbLogBegin();

    HbLogEnd();
}

void ToolsMainWindow::testApplicationHelper()
{

}

void ToolsMainWindow::testDictionnaryHelper()
{

}

void ToolsMainWindow::testEnum()
{

}

void ToolsMainWindow::testErrorCode()
{

}

void ToolsMainWindow::testMultipleSortFilterProxyModel()
{

}

void ToolsMainWindow::testNullable()
{

}

void ToolsMainWindow::testSingleton()
{

}

void ToolsMainWindow::testSteadyDateTime()
{

}

void ToolsMainWindow::testUid()
{

}

void ToolsMainWindow::testUidGenerator()
{

}

void ToolsMainWindow::testHttpRequester()
{

}

void ToolsMainWindow::testTimeoutNetworkReplies()
{

}

