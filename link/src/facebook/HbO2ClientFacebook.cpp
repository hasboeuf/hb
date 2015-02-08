// Local
#include <facebook/HbO2ClientFacebook.h>

const QString FB_ERROR             = QStringLiteral( "error" );
const QString FB_ERROR_REASON      = QStringLiteral( "error_reason" );
const QString FB_ERROR_DESCRIPTION = QStringLiteral( "error_description" );

const QUrl HbO2ClientFacebook::endPoint() const
{
    return QUrl( QStringLiteral( "https://www.facebook.com/dialog/oauth" ) );
}

const QHash< QString, QString > HbO2ClientFacebook::codeRequest() const
{
    QHash< QString, QString > request;
    request.insert( OAUTH2_RESPONSE_TYPE, OAUTH2_GRANT_CODE );
    request.insert( OAUTH2_CLIENT_ID,     mClientId );
    request.insert( OAUTH2_REDIRECT_URI,  mRedirectUri );
    request.insert( OAUTH2_SCOPE,         mScope );

    return request;
}

auto HbO2ClientFacebook::codeResponse( const QHash< QString, QString > & response ) -> LinkStatus
{
    if ( response.contains( FB_ERROR ) )
    {
        mErrorString += FB_ERROR + ": " + response.value( FB_ERROR ) + ";";
        mErrorString += FB_ERROR_REASON + ": " + response.value( FB_ERROR_REASON ) + ";";
        mErrorString += FB_ERROR_DESCRIPTION + ": " + response.value( FB_ERROR_DESCRIPTION ) + ";";

        return UNLINKED;
    }
    else if( response.contains( OAUTH2_CODE ) )
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

