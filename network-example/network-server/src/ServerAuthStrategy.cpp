// Qt
// Hb
#include <contract/auth/HbAuthRequestContract.h>
// Local
#include <ServerAuthStrategy.h>

using namespace hb::network;
using namespace hb::networkexample;

bool ServerAuthStrategy::tryLogin( const HbAuthRequestContract * contract )
{
    return true;
}

authstgy ServerAuthStrategy::type() const
{
    return HbAuthRequestContract::AUTH_USER + 0;
}

