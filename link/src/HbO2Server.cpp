// Qt
#include <QtCore/QUrlQuery>
#include <QtCore/QPair>
// Hb
#include <HbLogService.h>
#include <core/HbDictionaryHelper.h>
// Local
#include <HbO2Server.h>

using namespace hb::link;

HbO2Server::~HbO2Server()
{
    printf( "~HbO2Server\n");
}

bool HbO2Server::isValid() const
{
    if( !HbO2::isValid() )
    {
        return false;
    }

    if( mCode.isEmpty() || mClientSecret.isEmpty() )
    {
        return false;
    }

    return true;
}

bool HbO2Server::link()
{
    if( !HbO2::link() )
    {
        return false;
    }

    QUrl url( endPoint() );

    QUrlQuery request( url );
    request.setQueryItems( HbDictionaryHelper::toPairList< QString, QString >( tokenRequest() ) );
    url.setQuery( request );

    QNetworkRequest token_request( url );
    QNetworkReply * token_reply = mManager.get( token_request );

    mReplies.add( token_reply );

    connect( token_reply, &QNetworkReply::finished, this, &HbO2Server::onTokenResponseReceived, Qt::UniqueConnection );
    connect( token_reply, ( void ( QNetworkReply:: * )( QNetworkReply::NetworkError ) )( &QNetworkReply::error ),
             this, &HbO2Server::onTokenResponseError, Qt::UniqueConnection );

    return true;
}

void HbO2Server::onTokenResponseReceived()
{
    QNetworkReply * token_reply = dynamic_cast< QNetworkReply * >( sender() );
    q_assert_ptr( token_reply );

    HbInfo( "Token response received.");

    if ( token_reply->error() == QNetworkReply::NoError)
    {

        QByteArray data = token_reply->readAll();
        QString content( data );

        HbInfo( "Token content: %s", HbLatin1( content ) );

        if( tokenResponse( HbO2::getUrlItems( content ) ) == LINKED )
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

    //token_reply->deleteLater(); TODO TMP
}

void HbO2Server::onTokenResponseError( QNetworkReply::NetworkError error )
{
    QNetworkReply * token_reply = dynamic_cast< QNetworkReply * >( sender() );
    q_assert_ptr( token_reply );

    mLinkStatus = UNLINKED;
    mErrorString = token_reply->errorString();

    HbInfo( "Token response error. (%s)", HbLatin1( mErrorString ) );

    emit linkFailed( mErrorString );

    //token_reply->deleteLater(); TODO TMP
}

void HbO2Server::setClientSecret( const QString & client_secret )
{
    mClientSecret = client_secret;
}

const QString & HbO2Server::clientSecret() const
{
    return mClientSecret;
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
