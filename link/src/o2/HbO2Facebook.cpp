#include <o2/HbO2Facebook.h>

const QString FB_ERROR             = QStringLiteral( "error" );
const QString FB_ERROR_REASON      = QStringLiteral( "error_reason" );
const QString FB_ERROR_DESCRIPTION = QStringLiteral( "error_description" );

HbO2Facebook::HbO2Facebook()
{
}

const QUrl HbO2Facebook::endPoint() const
{
    return QUrl( QStringLiteral( "https://www.facebook.com/dialog/oauth" ) );
}

const QHash< QString, QString > HbO2Facebook::codeRequest() const
{
    QHash< QString, QString > request;
    request.insert( OAUTH2_RESPONSE_TYPE, OAUTH2_GRANT_CODE );
    request.insert( OAUTH2_CLIENT_ID,     clientId() );
    request.insert( OAUTH2_REDIRECT_URI,  redirectUri() );
    request.insert( OAUTH2_SCOPE,         scope() );

    return request;
}

auto HbO2Facebook::codeResponse( const QHash< QString, QString > & response ) -> LinkStatus
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

