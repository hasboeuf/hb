// Qt
#include <QtCore/QUrlQuery>
#include <QtCore/QPair>
// Hb
#include <HbLogService.h>
// Local
#include <o2/HbO2.h>
#include <HbLinkConstant.h>
#include <HbLinkServer.h>

using namespace hb::link;

HbO2::HbO2()
{
    mLocalPort = 0;
    mLinked = false;
}

bool HbO2::isValid() const
{
    if( mLocalPort == 0 )
    {
        return false;
    }

    return true;
}

void HbO2::link()
{
    if( mLinked )
    {
        HbInfo( "HbO2 already linked." );
    }

    if( !isValid() )
    {
        HbError( "HbO2 not valid." );
        return;
    }

    if( mReplyServer.isListening() )
    {
        mReplyServer.close();
    }

    mReplyServer.listen( QHostAddress::Any, mLocalPort );
    connect( &mReplyServer, &HbLinkServer::parametersReceived, this, &HbO2::onParametersReceived );

    QList< QPair< QString, QString > > parameters;
    parameters.append( qMakePair( OAUTH2_RESPONSE_TYPE, QStringLiteral( "code" ) ) );
    parameters.append( qMakePair( OAUTH2_CLIENT_ID,     mClientId ) );
    parameters.append( qMakePair( OAUTH2_REDIRECT_URI,  mRedirectUri ) );

    QUrl url( mRequestUrl );

    QUrlQuery query( url );
    query.setQueryItems( parameters );
    url.setQuery( query );

    HbInfo( "Url to open: %s", HbLatin1( url.toString() ) );

    emit openBrowser( url );
}

void HbO2::onParametersReceived(const QMap<QString, QString> query_parameters )
{
    if ( query_parameters.contains("error") )
    {
        HbError( "Verification failed." );
        emit linkingFailed();
        return;
    }
    else
    {
        HbInfo( "Verification succeed." );
    }


    // Save access code
    setCode( query_parameters.value( OAUTH2_CODE ) );

    HbInfo( "Code received: %s", HbLatin1( mCode ) );

}

void HbO2::setClientId( const QString & client_id )
{
    mClientId = client_id;
}

void HbO2::setLocalPort( quint16 local_port )
{
    mLocalPort = local_port;
    mRedirectUri = REDIRECT_URI.arg( mLocalPort );
}

void HbO2::setCode( const QString & code )
{
    mCode = code;
}

const QString & HbO2::clientId() const
{
    return mClientId;
}

quint16 HbO2::localPort() const
{
    return mLocalPort;
}

const QString & HbO2::code() const
{
    return mCode;
}

const QString & HbO2::redirectUri() const
{
    return mRedirectUri;
}

void HbO2::setRequestUrl( QString request_url )
{
    mRequestUrl = request_url;
}
