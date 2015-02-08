// Qt
#include <QtCore/QUrlQuery>
#include <QtCore/QPair>
// Hb
#include <HbLogService.h>
#include <core/HbDictionaryHelper.h>
// Local
#include <HbO2.h>

using namespace hb::link;

HbO2::HbO2()
{
    mLinkStatus = UNLINKED;
}

bool HbO2::isValid() const
{
    if( !QUrl( mRedirectUri ).isValid() || mClientId.isEmpty() || endPoint().isEmpty() )
    {
        return false;
    }

    return true;
}

bool HbO2::link()
{
    if( mLinkStatus != UNLINKED)
    {
        HbInfo( "HbO2 already linked or in linking." );
        return false;
    }

    if( !isValid() )
    {
        HbError( "HbO2 not valid." );
        return false;
    }

    mLinkStatus = LINKING;

    return true;
}

QHash< QString, QString > HbO2::getUrlItems( const QString & content )
{
    QUrl url( ENRICHED_URI_BASE + content );
    QUrlQuery response( url );

    HbInfo( "URLLLL=%s", HbLatin1( url.toString() ) );

    return HbDictionaryHelper::toHash< QString, QString >( response.queryItems() );
}

const QString & HbO2::errorString() const
{
    return mErrorString;
}

void HbO2::setClientId( const QString & client_id )
{
    mClientId = client_id;
}

const QString & HbO2::clientId() const
{
    return mClientId;
}

const QString & HbO2::redirectUri() const
{
    return mRedirectUri;
}

const QString & HbO2::code() const
{
    return mCode;
}


