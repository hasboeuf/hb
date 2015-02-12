// Qt
// Hb
#include <contract/auth/HbAuthRequestContract.h>
// Local
#include <ServerAuthStrategy.h>

using namespace hb::networkexample;

HbNetworkProtocol::AuthStatus ServerAuthStrategy::tryLogin( const HbAuthRequestContract * contract )
{
    return HbNetworkProtocol::AUTH_BAD;
}

