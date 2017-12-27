// Qt
#include <QtCore/QDebug>
#include <QtNetwork/QAbstractSocket>
// Hb
#include <HbLoggerStream.h>
#include <HbLogManager.h>

using namespace hb::log;

const char * HbLoggerStream::DEFAULT_LOCAL_SERVER_NAME = "HB_LOG";

HbLoggerStream::HbLoggerStream( HbLogManager * parent ) :
    QObject( parent )
{
    q_assert_x( parent, "HbLoggerStream", "HbLogManager not defined" );

    qRegisterMetaType< QAbstractSocket::SocketError >( "QAbstractSocket::SocketError" );
}
