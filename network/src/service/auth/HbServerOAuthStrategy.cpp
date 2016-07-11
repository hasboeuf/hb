// Hb
#include <HbLogService.h>
#include <HbO2Server.h>
// Local
#include <service/auth/HbAuthService.h>
#include <service/auth/HbServerOAuthStrategy.h>
#include <contract/auth/HbOAuthRequestContract.h>
#ifdef DEV
#include <mock/HbNetworkUserInfoMock.h>
#endif

using namespace hb::network;
using namespace hb::link;

HbServerOAuthStrategy::HbServerOAuthStrategy() :
    HbServerAuthStrategy()
{
}

HbServerOAuthStrategy::~HbServerOAuthStrategy()
{
    reset();
}

void HbServerOAuthStrategy::reset()
{
    qDeleteAll( mPendingToken.keys() );
    mPendingToken.clear();
    mPendingRequest.clear();
}

void HbServerOAuthStrategy::setConfig( const HbO2ServerConfig & config )
{
    mConfig = config;
}

void HbServerOAuthStrategy::onLinkFailed(const QString & error )
{
    HbLogBegin();
    HbO2Server * server_auth = dynamic_cast< HbO2Server * >( sender() );
    q_assert_ptr( server_auth );
    q_assert( mPendingToken.contains( server_auth ) );

    HbInfo( "Server link failed for user %s ( %s ).", HbLatin1( server_auth->config().clientId() ), HbLatin1( error ) );

    networkuid sender = mPendingToken.take( server_auth );

    server_auth->deleteLater();

    emit authFailed( sender, HbNetworkProtocol::AUTH_OAUTH_KO, error );
    HbLogEnd();
}
