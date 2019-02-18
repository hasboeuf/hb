#ifndef HBAUTHSTRATEGY_H
#define HBAUTHSTRATEGY_H

/*! \file HbAuthStrategy.h */

// Qt
// Hb
// Local
#include <HbNetwork.h>
#include <contract/HbNetworkProtocol.h>
#include <user/HbNetworkUserInfo.h>

namespace hb {
namespace network {
/*!
 * TODOC
 */
class HB_NETWORK_DECL HbAuthStrategy : public QObject {
public:
    HbAuthStrategy() = default;
    virtual ~HbAuthStrategy() = default;

    virtual void reset() = 0;

    virtual authstgy type() const = 0;
};
} // namespace network
} // namespace hb

using hb::network::HbAuthStrategy;

#endif // HBAUTHSTRATEGY_H
