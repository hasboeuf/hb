// Qt
#include <QtCore/QString>
// Hb
#include <HbLogService.h>
#include <HbLoggerOutputs.h>
#include <core/HbDictionaryHelper.h>
// Local
#include <ToolsMainWindow.h>

using namespace hb::tools;
using namespace hb::log;
using namespace hb::toolsexample;

ToolsMainWindow::ToolsMainWindow( QWidget * parent ) :
    QMainWindow( parent )
{
    // Ui
    setupUi( this );
    setWindowTitle( "Tools" );

    // Log
    HbLogService::logger()->setFormat( HbLogger::OUTPUT_LEVEL |
                                       HbLogger::OUTPUT_TIME  |
                                       HbLogger::OUTPUT_TEXT );
    QString error;
    if( HbLogService::outputs()->addGuiOutput( ui_qw_log->logNotifier() ) == 0 )
    {
        printf( "HbLog error: %s", HbLatin1( error ) );
    }

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

}

ToolsMainWindow::~ToolsMainWindow()
{
}

void ToolsMainWindow::testApplicationHelper()
{
    HbWarning( "== DEMO == HbApplicationHelper" );
    HbInfo( "See main.cpp::main() function." );
}

void ToolsMainWindow::testDictionnaryHelper()
{
    HbWarning( "== DEMO == HbDictionnaryHelper" );
    QList< QPair< qint8, QString > > list;
    list.append( qMakePair( 1, QStringLiteral( "one"  ) ) );
    list.append( qMakePair( 2, QStringLiteral( "two"  ) ) );
    list.append( qMakePair( 3, QStringLiteral( "three") ) );
    list.append( qMakePair( 4, QStringLiteral( "four" ) ) );
    list.append( qMakePair( 5, QStringLiteral( "five" ) ) );

    auto it_list = list.begin();
    while( it_list != list.end() )
    {
        HbInfo( "list key=%d value=%s.", it_list->first, HbLatin1( it_list->second ) );
        ++it_list;
    }

    auto map = HbDictionaryHelper::toHash( list );
    auto it_map = map.constBegin();
    while( it_map != map.constEnd() )
    {
        HbInfo( "map key=%d value=%s.", it_map.key(), HbLatin1( it_map.value() ) );
        ++it_map;
    }

    auto list2 = HbDictionaryHelper::toPairList( map );
    it_list = list2.begin();
    while( it_list != list2.end() )
    {
        HbInfo( "list2 key=%d value=%s.", it_list->first, HbLatin1( it_list->second ) );
        ++it_list;
    }

}

void ToolsMainWindow::testEnum()
{
    HbWarning( "== DEMO == HbEnum" );
}

void ToolsMainWindow::testErrorCode()
{
    HbWarning( "== DEMO == HbErrorCode" );
}

void ToolsMainWindow::testMultipleSortFilterProxyModel()
{
    HbWarning( "== DEMO == HbMultipleSortFilterProxyModel" );
}

void ToolsMainWindow::testNullable()
{
    HbWarning( "== DEMO == HbNullable" );

    HbNullable< qint16 > nullablle_int;
    HbInfo( "isNull=%d", nullablle_int.isNull() );
    HbInfo( "value=%d", nullablle_int.value( 89 ) );

    nullablle_int = 39;
    HbInfo( "isNull=%d", nullablle_int.isNull() );
    HbInfo( "value=%d", nullablle_int.value( 89 ) );
}

void ToolsMainWindow::testSingleton()
{
    HbWarning( "== DEMO == HbSingleton" );
}

void ToolsMainWindow::testSteadyDateTime()
{
    HbWarning( "== DEMO == HbSteadyDateTime" );
}

void ToolsMainWindow::testUid()
{
    HbWarning( "== DEMO == HbUid" );
}

void ToolsMainWindow::testUidGenerator()
{
    HbWarning( "== DEMO == HbUidGenerator" );
}

void ToolsMainWindow::testHttpRequester()
{
    HbWarning( "== DEMO == HbHttpRequester" );
}

void ToolsMainWindow::testTimeoutNetworkReplies()
{
    HbWarning( "== DEMO == HbTimeoutNetworkReplies" );
}

