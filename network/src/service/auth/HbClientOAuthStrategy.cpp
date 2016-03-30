// Qt
#include <QtGui/QDesktopServices>
// Hb
#include <HbLogService.h>
// Local
#include <service/auth/HbAuthService.h>
#include <service/auth/HbClientOAuthStrategy.h>
#include <service/auth/HbClientAuthLoginObject.h>
#include <contract/auth/HbOAuthRequestContract.h>

using namespace hb::network;
using namespace hb::link;

void HbClientOAuthStrategy::setConfig( const HbO2ClientConfig & config )
{
    mConfig = config;
}

void HbClientOAuthStrategy::reset()
{
    mPendingCodes.clear();
}

void HbClientOAuthStrategy::onOpenBrower( const QUrl & url )
{
    HbInfo( "Opening browser on %s", HbLatin1( url.toString() ) );
    QDesktopServices::openUrl( url );
}

void HbClientOAuthStrategy::onLinkSucceed()
{
    HbO2Client * client = dynamic_cast< HbO2Client * >( sender() );
    q_assert_ptr( client );
    q_assert( mPendingCodes.contains( client ) );

    networkuid socket_uid = mPendingCodes.value( client );

    HbOAuthRequestContract * contract = new HbOAuthRequestContract();
    contract->setType( type() );
    contract->setCode( client->code() );
    contract->setRedirectUri( client->redirectUri() );

    mPendingCodes.remove( client );
    client->deleteLater();

    emit authContractReady( socket_uid, contract );
}

void HbClientOAuthStrategy::onLinkFailed()
{
    HbO2Client * client = dynamic_cast< HbO2Client * >( sender() );
    q_assert_ptr( client );
    q_assert( mPendingCodes.contains( client ) );

    networkuid socket_uid = mPendingCodes.value( client );

    mPendingCodes.remove( client );
    client->deleteLater();

    emit authContractFailed( socket_uid, "OAuth link failed." );
}


