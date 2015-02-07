// Local
#include <server/HbO2ServerFacebook.h>

const QUrl HbO2ServerFacebook::endPoint() const
{
    return QUrl( QStringLiteral( "https://graph.facebook.com/oauth/access_token" ) );
}


const QHash< QString, QString > HbO2ServerFacebook::tokenRequest() const
{
    QHash< QString, QString > request;
    request.insert( OAUTH2_CLIENT_ID,     mClientId );
    request.insert( OAUTH2_CLIENT_SECRET, mClientSecret);
    request.insert( OAUTH2_CODE,          mCode);
    request.insert( OAUTH2_REDIRECT_URI,  mRedirectUri);
    return request;
}

auto HbO2ServerFacebook::tokenResponse( const QHash< QString, QString > & response ) -> LinkStatus
{

}
