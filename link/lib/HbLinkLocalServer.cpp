// Qt
#include <QtNetwork/QTcpSocket>
#include <QtCore/QByteArray>
#include <QtCore/QUrl>
#include <QtCore/QUrlQuery>
// Hb
#include <HbLogService.h>
#include <core/HbDictionaryHelper.h>
// Local
#include <HbLinkLocalServer.h>
#include <HbO2.h>

using namespace hb::link;

HbLinkLocalServer::HbLinkLocalServer( QObject * parent ) :
    QTcpServer( parent )
{
    connect( this, &QTcpServer::newConnection, this, &HbLinkLocalServer::onIncomingConnection, Qt::UniqueConnection );
}

void HbLinkLocalServer::onIncomingConnection()
{
    QTcpSocket * socket = nextPendingConnection();

    connect( socket, &QTcpSocket::readyRead, this, &HbLinkLocalServer::onReadyRead, Qt::UniqueConnection );
    connect( socket, &QTcpSocket::disconnected, socket, &QObject::deleteLater, Qt::UniqueConnection );
}

void HbLinkLocalServer::onReadyRead()
{
    QTcpSocket *socket = dynamic_cast< QTcpSocket * >( sender() );
    if ( !socket )
    {
        qWarning() << "Null socket";
        return;
    }

    QByteArray reply;
    QByteArray content;
    content.append( QStringLiteral( "<html><head><script>window.close();</script></head></html>" ) );
    reply.append( QStringLiteral( "HTTP/1.0 200 OK \r\n" ) );
    reply.append( QStringLiteral( "Content-Type: text/html; charset=\"utf-8\"\r\n" ) );
    reply.append( QString( "Content-Length: %1\r\n\r\n" ).arg( content.size() ) );
    reply.append( content );

    qDebug() << "Reply written:" << reply.constData();

    socket->write( reply );

    QByteArray data = socket->readAll();
    auto response = parseResponse( data );

    socket->disconnectFromHost();
    close();

    emit responseReceived( response );
}

QHash< QString, QString > HbLinkLocalServer::parseResponse( QByteArray & data )
{
    QString content = QString( data );

// Google response example:
//
//    GET /favicon.ico HTTP/1.1
//    Host: localhost:8080
//    Connection: keep-alive
//    User-Agent: Mozilla/5.0 (Windows NT 10.0; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/48.0.2564.116 Safari/537.36
//    Accept: */*
//    Referer: http://localhost:8080/?code={CODE}
//    Accept-Encoding: gzip, deflate, sdch
//    Accept-Language: fr-FR,fr;q=0.8,en-US;q=0.6,en;q=0.4
//
// Facebook response example:
//
//    GET /?code={CODE} HTTP/1.1
//    Host: localhost:8080
//    Connection: keep-alive
//    Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,*/*;q=0.8
//    Upgrade-Insecure-Requests: 1
//    User-Agent: Mozilla/5.0 (Windows NT 10.0; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/48.0.2564.116 Safari/537.36
//    Accept-Encoding: gzip, deflate, sdch
//    Accept-Language: fr-FR,fr;q=0.8,en-US;q=0.6,en;q=0.4
//
// Aim here: extract code={CODE}

    qDebug() << "Response content received:" << content;

    content = content.simplified(); // All white-space characters become space.

    QRegExp capture_expr("(/\\?\\S+)"); // Matches "/?" followed by non white-space characters => e.g.: "/?var1=foo&var2=bar"
    capture_expr.indexIn( content );
    QStringList result = capture_expr.capturedTexts();
    result.removeDuplicates(); // Regexp can capture in different ways same extracts.

    if( result.size() > 0 )
    {
        if( result.size() == 1 )
        {
            content = result.first();
            content = content.remove( 0, 2 ); // Remove "/?".
        }
        else
        {
            qWarning() << "Parsing found more than one url pattern:" << result.join( QChar::Space );
        }
    }
    else
    {
        qWarning() << "Parsing found 0 url pattern";
    }

    qDebug() << "Simplified response content:" << content;

    return HbO2::getUrlItems( content );
}

