// Qt
#include <QtCore/QUrlQuery>
#include <QtCore/QPair>
// Hb
#include <HbLogService.h>
#include <core/HbDictionaryHelper.h>
// Local
#include <HbO2Client.h>

using namespace hb::link;

HbO2Client::HbO2Client()
{
    mLocalPort = 0;
}

HbO2Client::HbO2Client( const HbO2Client & source ) :
    HbO2( source )
{
    if( &source != this )
    {
        mScope     = source.mScope;
        mLocalPort = source.mLocalPort;
    }
}

HbO2Client & HbO2Client::operator=( const HbO2Client & source )
{
    if( &source != this )
    {
        HbO2::operator =( source );

        mScope     = source.mScope;
        mLocalPort = source.mLocalPort;
    }
    return ( *this );
}

bool HbO2Client::isValid() const
{
    if( !HbO2::isValid() )
    {
        return false;
    }

    if( mLocalPort == 0 )
    {
        return false;
    }

    return true;
}

bool HbO2Client::link()
{
    if( !HbO2::link() )
    {
        return false;
    }

    if( mReplyServer.isListening() )
    {
        mReplyServer.close();
    }

    mReplyServer.listen( QHostAddress::Any, mLocalPort );
    connect( &mReplyServer, &HbLinkLocalServer::responseReceived, this, &HbO2Client::onCodeResponseReceived );

    QUrl url( endPoint() );

    QUrlQuery request( url );
    request.setQueryItems( HbDictionaryHelper::toPairList< QString, QString >( codeRequest() ) );
    url.setQuery( request );

    HbInfo( "Url to open: %s", HbLatin1( url.toString() ) );

    emit openBrowser( url );

    return true;
}

void HbO2Client::onCodeResponseReceived( const QHash< QString, QString > response )
{
    if( codeResponse( response ) == LINKED )
    {
        HbInfo( "Verification succeed." );
        HbInfo( "Code received: %s", HbLatin1( mCode ) );
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

void HbO2Client::setLocalPort( quint16 local_port )
{
    mLocalPort = local_port;
    mRedirectUri = REDIRECT_URI.arg( mLocalPort );
}

quint16 HbO2Client::localPort() const
{
    return mLocalPort;
}

void HbO2Client::addScope( const QString & permission )
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

const QString & HbO2Client::scope() const
{
    return mScope;
}

bool HbO2Client::read( QDataStream & stream )
{
    if( HbO2::read( stream ) )
    {
        stream >> mScope;
        stream >> mLocalPort;

        return ( stream.status() == QDataStream::Ok );
    }

    return false;
}

bool HbO2Client::write( QDataStream & stream ) const
{
    if( HbO2::write( stream ) )
    {
        stream << mScope;
        stream << mLocalPort;

        return ( stream.status() == QDataStream::Ok );
    }

    return false;
}
