// Qt
#include <QtCore/QUrlQuery>
#include <QtCore/QPair>
// Hb
#include <HbLogService.h>
#include <core/HbDictionaryHelper.h>
// Local
#include <o2/HbO2.h>
#include <HbLinkServer.h>

using namespace hb::link;

HbO2::HbO2()
{
    mLocalPort = 0;
    mLinkStatus = UNLINKED;
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
    if( mLinkStatus != UNLINKED)
    {
        HbInfo( "HbO2 already linked or in linking." );
    }

    if( !isValid() )
    {
        HbError( "HbO2 not valid." );
        return;
    }

    mLinkStatus = LINKING;

    if( mReplyServer.isListening() )
    {
        mReplyServer.close();
    }

    mReplyServer.listen( QHostAddress::Any, mLocalPort );
    connect( &mReplyServer, &HbLinkServer::responseReceived, this, &HbO2::onResponseReceived );

    QUrl url( endPoint() );

    QUrlQuery request( url );
    request.setQueryItems( HbDictionaryHelper::toPairList< QString, QString >( codeRequest() ) );
    url.setQuery( request );

    HbInfo( "Url to open: %s", HbLatin1( url.toString() ) );

    emit openBrowser( url );
}

void HbO2::onResponseReceived( const QHash< QString, QString > response )
{
    if( codeResponse( response ) == LINKED )
    {
        HbInfo( "Verification succeed." );
        HbInfo( "Code received: %s", HbLatin1( mCode ) );
        mLinkStatus = LINKED;
        emit linkingSucceed();
    }
    else
    {
        HbError( "Verification failed. (%s)", HbLatin1( mErrorString ) );
        mLinkStatus = UNLINKED;

        emit linkingFailed( mErrorString );
    }
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

void HbO2::addScope( const QString & permission )
{
    if( !permission.isEmpty() )
    {
        if( !mScope.isEmpty() )
        {
            mScope += QStringLiteral( "," );
        }
        mScope += permission;
    }
}

const QString & HbO2::errorString() const
{
    return mErrorString;
}

const QString & HbO2::scope() const
{
    return mScope;
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

