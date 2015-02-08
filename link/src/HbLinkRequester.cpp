// Qt
#include <QtCore/QUrlQuery>
#include <QtCore/QPair>
#include <QtCore/QJsonDocument>
// Hb
#include <HbLogService.h>
#include <core/HbDictionaryHelper.h>
// Local
#include <HbLinkRequester.h>

using namespace hb::link;

HbLinkRequester::HbLinkRequester()
{

}

qint64 HbLinkRequester::processRequest( const QUrl &url, quint32 timeout )
{
    QNetworkRequest request( url );
    QNetworkReply * reply = mManager.get( request );

    qint64 id = mReplies.add( reply, timeout );
    if( id > 0)
    {
        connect( reply, &QNetworkReply::finished, this, &HbLinkRequester::onFinished );
        connect( reply, ( void ( QNetworkReply:: * )( QNetworkReply::NetworkError ) )( &QNetworkReply::error ),
                 this, &HbLinkRequester::onError );
    }

    return id;
}

void HbLinkRequester::onFinished()
{
    QNetworkReply * reply = dynamic_cast< QNetworkReply * >( sender() );
    q_assert_ptr( reply );

    qint64 id = mReplies.id( reply );

    if ( reply->error() == QNetworkReply::NoError)
    {

        QString data( reply->readAll() );
        QJsonDocument doc = QJsonDocument::fromJson( data.toUtf8() );

        emit requestFinished( id, doc );
    }
    else
    {
        emit requestError( id, reply->errorString() );
    }

    reply->deleteLater();
}

void HbLinkRequester::onError( const QNetworkReply::NetworkError & error )
{
    QNetworkReply * reply = dynamic_cast< QNetworkReply * >( sender() );
    q_assert_ptr( reply );

    qint64 id = mReplies.id( reply );

    emit requestError( id, reply->errorString() );

    reply->deleteLater();
}
