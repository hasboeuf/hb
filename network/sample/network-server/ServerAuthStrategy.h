#ifndef SERVERAUTHSTRATEGY_H
#define SERVERAUTHSTRATEGY_H

// Qt
// Hb
#include <contract/HbNetworkProtocol.h>
#include <service/auth/HbServerAuthStrategy.h>
// Local

namespace hb {
namespace networkexample {

class ServerAuthStrategy : public hb::network::HbServerAuthStrategy {
public:
    ServerAuthStrategy() = default;
    virtual ~ServerAuthStrategy() = default;

    virtual void reset();

    virtual bool checkLogin(const HbAuthRequestContract* contract);
    virtual authstgy type() const;
};
} // namespace networkexample
} // namespace hb

#endif // SERVERAUTHSTRATEGY_H
