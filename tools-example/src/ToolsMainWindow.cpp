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
    if( HbLogService::outputs()->addConsoleOutput( &error ) == 0 )
    {
        printf( "HbLog error: %s", HbLatin1( error ) );
    }

    HbLogBegin();

    // Ui
    setupUi( this );
    setWindowTitle( "Tools" );

    HbLogEnd();
}

ToolsMainWindow::~ToolsMainWindow()
{
    HbLogBegin();

    HbLogEnd();
}
