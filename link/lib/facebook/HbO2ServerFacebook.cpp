// Qt
#include <QtGui/QDesktopServices>
#include <QtCore/QUrlQuery>
// Hb
#include <HbLogService.h>
#include <core/HbDictionaryHelper.h>
// Local
#include <facebook/HbO2ServerFacebook.h>

HbO2ServerFacebook::HbO2ServerFacebook()
{
    mRequestType = REQUEST_GET;
}

void HbO2ServerFacebook::addField( const QString & field )
{
    if( !field.isEmpty() )
    {
        if( !mFields.isEmpty() )
        {
            mFields += QStringLiteral( "," );
        }
        mFields += field;
    }
}

void HbO2ServerFacebook::setFields( const QString & fields )
{
    if( mFields.isEmpty() )
    {
        mFields = fields;
    }
    else
    {
        qWarning() << "Scope is not empty";
    }
}

const QString & HbO2ServerFacebook::fields() const
{
    return mFields;
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

HbO2::LinkStatus HbO2ServerFacebook::tokenResponse( const QByteArray & data )
{
    QHash< QString, QString > response = HbO2::getUrlItems( QString( data ) );

    if( response.contains( OAUTH2_ACCESS_TOKEN ) )
    {
        mToken           = response.value( OAUTH2_ACCESS_TOKEN );
        mTokenExpiration = response.value( FB_EXPIRES_IN ).toInt();

        return LINKED;
    }
    else
    {
        mErrorString += "undefined error";
        return UNLINKED;
    }
}
