// Qt
#include <QtCore/QUrlQuery>
#include <QtCore/QPair>
// Hb
#include <HbLogService.h>
#include <core/HbDictionaryHelper.h>
// Local
#include <HbO2Server.h>

using namespace hb::link;

HbO2Server::HbO2Server()
{
    mRequestType = REQUEST_POST;
}

bool HbO2Server::isValid() const
{
    if( !HbO2::isValid() )
    {
        return false;
    }

    if( mCode.isEmpty() )
    {
        return false;
    }

    if( !mConfig.isValid() )
    {
        return false;
    }

    return true;
}

HbO2ServerConfig & HbO2Server::config()
{
    return mConfig;
}

const HbO2ServerConfig & HbO2Server::config() const
{
    return mConfig;
}

void HbO2Server::onTokenResponseReceived()
{
    QNetworkReply * token_reply = dynamic_cast< QNetworkReply * >( sender() );
    q_assert_ptr( token_reply );

    qDebug() << "Token response received";

    if ( token_reply->error() == QNetworkReply::NoError)
    {

        QByteArray data = token_reply->readAll();

        qDebug() << "Token content:" << data;

        if( tokenResponse( data ) == LINKED )
        {
            qDebug() << "Verification succeed";
            qDebug() << "Token received:" << mToken;
            mLinkStatus = LINKED;
            emit linkSucceed();
        }
        else
        {
            qWarning() << "Verification failed" << mErrorString;
            mLinkStatus = UNLINKED;

            emit linkFailed( mErrorString );
        }
    }
    else
    {
        mLinkStatus = UNLINKED;
        mErrorString = token_reply->errorString();
        emit linkFailed( mErrorString );
    }

    token_reply->deleteLater();
}

void HbO2Server::onTokenResponseError( QNetworkReply::NetworkError error )
{
    Q_UNUSED( error )

    QNetworkReply * token_reply = dynamic_cast< QNetworkReply * >( sender() );
    q_assert_ptr( token_reply );

    mLinkStatus = UNLINKED;
    mErrorString = token_reply->errorString();

    qWarning() << "Token response error" << mErrorString;

    if( mErrorString.contains( "Error creating SSL context" ) )
    {
        qWarning() << "You might miss updated OpenSSL lib on your system";
    }

    emit linkFailed( mErrorString );

    token_reply->deleteLater();
}

void HbO2Server::setRedirectUri( const QString & redirect_uri )
{
    mRedirectUri = redirect_uri;
}

void HbO2Server::setCode( const QString & code )
{
    mCode = code;
}

const QString & HbO2Server::token() const
{
    return mToken;
}

qint32 HbO2Server::tokenExpiration() const
{
    return mTokenExpiration;
}

bool HbO2Server::link()
{
    if( !isValid() )
    {
        return false;
    }

    mLinkStatus = LINKING;

    QUrl url( endPoint() );

    if( mRequestType == REQUEST_GET )
    {
        QUrlQuery request( url );
        request.setQueryItems( HbDictionaryHelper::toPairList< QString, QString >( tokenRequest() ) );
        url.setQuery( request );
    }

    QNetworkRequest token_request( url );
    
    QNetworkReply * token_reply = nullptr;

    if( mRequestType == REQUEST_GET )
    {
        token_reply = mManager.get( token_request );
    }
    else // REQUEST_POST
    {
        token_request.setHeader( QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded" );

        QUrlQuery post_data;
        post_data.setQueryItems( HbDictionaryHelper::toPairList< QString, QString >( tokenRequest() ) );

        token_reply = mManager.post( token_request, post_data.toString( QUrl::FullyEncoded ).toUtf8() );
    }

    mReplies.add( token_reply );

    connect( token_reply, &QNetworkReply::sslErrors, [token_reply]() {
        token_reply->ignoreSslErrors();
    } );
    connect( token_reply, &QNetworkReply::finished, this, &HbO2Server::onTokenResponseReceived, Qt::UniqueConnection );
    connect( token_reply, ( void ( QNetworkReply:: * )( QNetworkReply::NetworkError ) )( &QNetworkReply::error ),
             this, &HbO2Server::onTokenResponseError, Qt::UniqueConnection );

    return true;
}
