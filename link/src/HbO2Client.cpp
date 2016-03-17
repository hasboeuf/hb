// Qt
#include <QtCore/QUrlQuery>
#include <QtCore/QPair>
// Hb
#include <HbLogService.h>
#include <core/HbDictionaryHelper.h>
// Local
#include <HbO2Client.h>

using namespace hb::link;

HbO2Client::HbO2Client( const HbO2Client & source ) :
    HbO2( source )
{
    if( &source != this )
    {
        mConfig = source.mConfig;
    }
}

HbO2Client & HbO2Client::operator=( const HbO2Client & source )
{
    if( &source != this )
    {
        HbO2::operator =( source );

        mConfig = source.mConfig;
    }
    return ( *this );
}

bool HbO2Client::isValid() const
{
    if( !HbO2::isValid() )
    {
        return false;
    }

    return mConfig.isValid();
}

HbO2ClientConfig & HbO2Client::config()
{
    return mConfig;
}

const HbO2ClientConfig & HbO2Client::config() const
{
    return mConfig;
}

bool HbO2Client::link()
{
    mRedirectUri = REDIRECT_URI.arg( mConfig.localPort() ); // Complete uri with the port.

    if( !isValid() )
    {
        return false;
    }

    mLinkStatus = LINKING;

    if( mReplyServer.isListening() )
    {
        mReplyServer.close();
    }

    mReplyServer.listen( QHostAddress::Any, mConfig.localPort() );
    connect( &mReplyServer, &HbLinkLocalServer::responseReceived, this, &HbO2Client::onCodeResponseReceived, Qt::UniqueConnection );

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

bool HbO2Client::read( QDataStream & stream )
{
    if( HbO2::read( stream ) )
    {
        stream >> mConfig;

        return ( stream.status() == QDataStream::Ok );
    }

    return false;
}

bool HbO2Client::write( QDataStream & stream ) const
{
    if( HbO2::write( stream ) )
    {
        stream << mConfig;

        return ( stream.status() == QDataStream::Ok );
    }

    return false;
}
