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

    HbInfo( "Token response received.");

    if ( token_reply->error() == QNetworkReply::NoError)
    {

        QByteArray data = token_reply->readAll();

        HbInfo( "Token content: %s", HbLatin1( QString( data ) ) );

        if( tokenResponse( data ) == LINKED )
        {
            HbInfo( "Verification succeed." );
            HbInfo( "Token received: %s", HbLatin1( mToken ) );
            mLinkStatus = LINKED;
            emit linkSucceed();
        }
        else
        {
            HbError( "Verification failed. (%s)", HbLatin1( mErrorString ) );
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

    HbInfo( "Token response error. (%s)", HbLatin1( mErrorString ) );

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
        QUrlQuery post_data;
        post_data.setQueryItems( HbDictionaryHelper::toPairList< QString, QString >( tokenRequest() ) );

        token_reply = mManager.post( token_request, post_data.toString( QUrl::FullyEncoded ).toUtf8() );
    }

    mReplies.add( token_reply );

    connect( token_reply, &QNetworkReply::finished, this, &HbO2Server::onTokenResponseReceived, Qt::UniqueConnection );
    connect( token_reply, ( void ( QNetworkReply:: * )( QNetworkReply::NetworkError ) )( &QNetworkReply::error ),
             this, &HbO2Server::onTokenResponseError, Qt::UniqueConnection );

    return true;
}
