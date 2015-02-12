// Qt
#include <QtCore/QUrlQuery>
#include <QtCore/QPair>
// Local
#include <HbGlobal.h>
#include <network/HbHttpRequester.h>

using namespace hb::link;

HbHttpRequester::HbHttpRequester()
{

}

quint64 HbHttpRequester::processRequest( const QUrl &url, quint32 timeout )
{
    QNetworkRequest request( url );
    QNetworkReply * reply = mManager.get( request );

    quint64 id = mReplies.add( reply, timeout );
    if( id >= 0)
    {
        connect( reply, &QNetworkReply::finished, this, &HbHttpRequester::onFinished );
        connect( reply, ( void ( QNetworkReply:: * )( QNetworkReply::NetworkError ) )( &QNetworkReply::error ),
                 this, &HbHttpRequester::onError );
    }

    return id;
}

void HbHttpRequester::onFinished()
{
    QNetworkReply * reply = dynamic_cast< QNetworkReply * >( sender() );
    q_assert_ptr( reply );

    quint64 id = mReplies.id( reply );

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

void HbHttpRequester::onError( const QNetworkReply::NetworkError & error )
{
    QNetworkReply * reply = dynamic_cast< QNetworkReply * >( sender() );
    q_assert_ptr( reply );

    quint64 id = mReplies.id( reply );

    emit requestError( id, reply->errorString() );

    reply->deleteLater();
}
