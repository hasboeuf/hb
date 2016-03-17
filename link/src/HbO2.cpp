// Qt
#include <QtCore/QUrlQuery>
#include <QtCore/QPair>
// Hb
#include <HbLogService.h>
#include <core/HbDictionaryHelper.h>
// Local
#include <HbO2.h>

using namespace hb::link;

HbO2::HbO2() :
    QObject()
{
    mLinkStatus = UNLINKED;
}

HbO2::HbO2( const HbO2 & source ) :
    QObject()
{
    if( &source != this )
    {
        mLinkStatus  = source.mLinkStatus;
        mErrorString = source.mErrorString;
        mCode        = source.mCode;
        mRedirectUri = source.mRedirectUri;
    }
}

HbO2 & HbO2::operator=( const HbO2 & source )
{
    if( &source != this )
    {
        mLinkStatus  = source.mLinkStatus;
        mErrorString = source.mErrorString;
        mCode        = source.mCode;
        mRedirectUri = source.mRedirectUri;
    }
    return ( *this );
}

bool HbO2::isValid() const
{
    if( mLinkStatus != UNLINKED)
    {
        HbInfo( "HbO2 already linked or in linking." );
        return false;
    }

    if( !QUrl( mRedirectUri ).isValid() || endPoint().isEmpty() )
    {
        HbError( "HbO2 not valid." );
        return false;
    }

    return true;
}

QHash< QString, QString > HbO2::getUrlItems( const QString & content )
{
    QUrl url( ENRICHED_URI_BASE + content );
    QUrlQuery response( url );

    return HbDictionaryHelper::toHash< QString, QString >( response.queryItems() );
}

const QString & HbO2::errorString() const
{
    return mErrorString;
}

HbO2::LinkStatus HbO2::linkStatus() const
{
    return mLinkStatus;
}

const QString & HbO2::redirectUri() const
{
    return mRedirectUri;
}

const QString & HbO2::code() const
{
    return mCode;
}

bool HbO2::read( QDataStream & stream )
{
    quint8 status;
    stream >> status;
    stream >> mErrorString;
    stream >> mCode;
    stream >> mRedirectUri;

    mLinkStatus = ( LinkStatus ) status;

    return ( stream.status() == QDataStream::Ok );
}

bool HbO2::write( QDataStream & stream ) const
{
    stream << ( quint8 ) mLinkStatus;
    stream << mErrorString;
    stream << mCode;
    stream << mRedirectUri;

    return ( stream.status() == QDataStream::Ok );
}

namespace hb
{
    namespace link
    {
        QDataStream & operator<<( QDataStream & stream, const HbO2 & o2 )
        {
            o2.write( stream );
            return stream;
        }

        QDataStream & operator>>( QDataStream & stream, HbO2 & o2 )
        {
            o2.read( stream );
            return stream;
        }
    }
}
