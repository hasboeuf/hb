// Local
#include <google/HbO2ClientGoogle.h>

HbO2ClientGoogle::HbO2ClientGoogle()
{
    mConfig.setScopeSeparator( " " );
}

const QUrl HbO2ClientGoogle::endPoint() const
{
    return QUrl( QStringLiteral( "https://accounts.google.com/o/oauth2/v2/auth" ) );
}

const QHash< QString, QString > HbO2ClientGoogle::codeRequest() const
{
    QHash< QString, QString > request;
    request.insert( OAUTH2_RESPONSE_TYPE, OAUTH2_GRANT_CODE );
    request.insert( OAUTH2_CLIENT_ID,     mConfig.clientId() );
    request.insert( OAUTH2_REDIRECT_URI,  mRedirectUri );
    request.insert( OAUTH2_SCOPE,         mConfig.scopesStr() );

    return request;
}

HbO2::LinkStatus HbO2ClientGoogle::codeResponse( const QHash< QString, QString > & response )
{
    if( response.contains( OAUTH2_CODE ) )
    {
        mCode = response.value( OAUTH2_CODE );
        return LINKED;
    }
    else
    {
        mErrorString += "undefined error";
        return UNLINKED;
    }
}
