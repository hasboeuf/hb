// Qt
#include <QtGui/QDesktopServices>
#include <QtCore/QUrlQuery>
// Hb
#include <HbLogService.h>
#include <core/HbDictionaryHelper.h>
// Local
#include <facebook/HbO2ServerFacebook.h>

void HbO2ServerFacebook::inspectToken( QString admin_token )
{
    if( mLinkStatus != LINKED )
    {
        HbError( "Get linked first." );
        return;
    }

    QHash< QString, QString > inspect_request;
    inspect_request.insert( FB_INPUT_TOKEN, mToken );
    inspect_request.insert( FB_TOKEN,       admin_token );

    QUrl url( QStringLiteral( "https://graph.facebook.com/debug_token" ) );
    QUrlQuery request( url );
    request.setQueryItems( HbDictionaryHelper::toPairList< QString, QString >( inspect_request ) );
    url.setQuery( request );

    QDesktopServices::openUrl( url );
}

const QUrl HbO2ServerFacebook::endPoint() const
{
    return QUrl( QStringLiteral( "https://graph.facebook.com/oauth/access_token" ) );
}

const QHash< QString, QString > HbO2ServerFacebook::tokenRequest() const
{
    QHash< QString, QString > request;
    request.insert( OAUTH2_CLIENT_ID,     mConfig.clientId() );
    request.insert( OAUTH2_CLIENT_SECRET, mConfig.clientSecret() );
    request.insert( OAUTH2_CODE,          mCode);
    request.insert( OAUTH2_REDIRECT_URI,  mRedirectUri);
    return request;
}

auto HbO2ServerFacebook::tokenResponse( const QHash< QString, QString > & response ) -> LinkStatus
{
    if( response.contains( FB_TOKEN ) )
    {
        mToken           = response.value( FB_TOKEN );
        mTokenExpiration = response.value( FB_EXPIRES_IN ).toInt();

        return LINKED;
    }
    else
    {
        mErrorString += "undefined error";
        return UNLINKED;
    }
}
