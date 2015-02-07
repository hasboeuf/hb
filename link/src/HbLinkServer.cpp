// Qt
#include <QtNetwork/QTcpSocket>
#include <QtCore/QByteArray>
#include <QtCore/QUrl>
#include <QtCore/QUrlQuery>
// Hb
#include <HbLogService.h>
#include <core/HbDictionaryHelper.h>
// Local
#include <HbLinkServer.h>

using namespace hb::link;

HbLinkServer::HbLinkServer( QObject * parent ) :
    QTcpServer( parent )
{
    connect( this, &QTcpServer::newConnection, this, &HbLinkServer::onIncomingConnection );
}

void HbLinkServer::onIncomingConnection()
{
    QTcpSocket * socket = nextPendingConnection();

    connect( socket, &QTcpSocket::readyRead, this, &HbLinkServer::onReadyRead, Qt::UniqueConnection );
    connect( socket, &QTcpSocket::disconnected, socket, &QObject::deleteLater );
}

void HbLinkServer::onReadyRead()
{
    QTcpSocket *socket = dynamic_cast< QTcpSocket * >( sender() );
    if ( !socket )
    {
        HbError( "Socket null." );
        return;
    }

    QByteArray reply;
    QByteArray content;
    content.append( QStringLiteral( "<html><head><script>window.close();</script></head></html>" ) );
    reply.append( QStringLiteral( "HTTP/1.0 200 OK \r\n" ) );
    reply.append( QStringLiteral( "Content-Type: text/html; charset=\"utf-8\"\r\n" ) );
    reply.append( QString( "Content-Length: %1\r\n\r\n" ).arg( content.size() ) );
    reply.append( content );

    HbInfo( "Reply written: %s", reply.constData() );

    socket->write( reply );

    QByteArray data = socket->readAll();
    auto response = parseResponse( data );

    socket->disconnectFromHost();
    close();

    emit responseReceived( response );
}

QHash< QString, QString > HbLinkServer::parseResponse( QByteArray & data )
{
    QString content = QString( data );

    HbInfo( "Response content received: %s", HbLatin1( content ) );

    content = content.split("\n").first();
    content.remove("GET");
    content.remove("HTTP/1.1");
    content = content.trimmed();
    content.prepend("http://localhost");

    HbInfo( "Simplifed response content: %s", HbLatin1( content ) );

    QUrl url( content );
    QUrlQuery response( url );

    return HbDictionaryHelper::toHash< QString, QString >( response.queryItems() );
}

