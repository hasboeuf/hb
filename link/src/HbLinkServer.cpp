// Qt
#include <QtNetwork/QTcpSocket>
#include <QtCore/QByteArray>
#include <QtCore/QUrl>
#include <QtCore/QUrlQuery>
// Hb
#include <HbLogService.h>
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
    content.append( QStringLiteral( "<HTML></HTML>" ) );
    reply.append( QStringLiteral( "HTTP/1.0 200 OK \r\n" ) );
    reply.append( QStringLiteral( "Content-Type: text/html; charset=\"utf-8\"\r\n" ) );
    reply.append( QString( "Content-Length: %1\r\n\r\n" ).arg( content.size() ) );
    reply.append( content );

    HbInfo( "Reply written: %s", reply.constData() );

    socket->write( reply );

    QByteArray data = socket->readAll();
    QMap<QString, QString> query_parameters = parseQueryParameters( data );

    socket->disconnectFromHost();
    close();

    emit parametersReceived( query_parameters );
}

QMap<QString, QString> HbLinkServer::parseQueryParameters( QByteArray & data )
{
    QString splited_line = QString( data );

    HbInfo( "Reply received: %s", HbLatin1( splited_line ) );

    splited_line = splited_line.split("\n").first();
    splited_line.remove("GET");
    splited_line.remove("HTTP/1.1");
    splited_line = splited_line.trimmed();
    splited_line.prepend("http://localhost");

    HbInfo( "Simplifed reply: %s", HbLatin1( splited_line ) );

    QUrl token_url( splited_line );
    QUrlQuery query( token_url );

    auto tokens = query.queryItems();
    QMap< QString, QString > query_parameter;

    for( int i = 0; i < tokens.size(); ++i )
    {
        QPair< QString, QString > pair = tokens.at( i );

        QString key   = pair.first;
        QString value = pair.second;

        HbDebug( "Add parameter key=%s, value=%s", HbLatin1( key ), HbLatin1( value ) );

        query_parameter.insert( pair.first, pair.second );
    }

    return query_parameter;
}

