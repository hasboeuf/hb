#ifndef HBSERVEROAUTHSTRATEGY_H
#define HBSERVEROAUTHSTRATEGY_H

// Qt
#include <QtCore/QHash>
// Hb
#include <config/HbO2ServerConfig.h>
// Local
#include <HbNetwork.h>
#include <contract/HbNetworkProtocol.h>
#include <contract/auth/HbAuthRequestContract.h> // Template.
#include <service/auth/HbServerAuthStrategy.h>

namespace hb {
namespace link {
class HbO2Server;
}

using namespace link;

namespace network {
/*!
 * TODOC
 */
class HB_NETWORK_DECL HbServerOAuthStrategy : public HbServerAuthStrategy {
    Q_OBJECT
public:
    HbServerOAuthStrategy();
    virtual ~HbServerOAuthStrategy();

    virtual void reset() override;

    virtual void setConfig(const HbO2ServerConfig& config);

    void onLinkFailed(const QString& error);

protected:
    QHash<HbO2Server*, networkuid> mPendingToken;
    QHash<quint64, networkuid> mPendingRequest;
    HbO2ServerConfig mConfig;
};
} // namespace network
} // namespace hb

using hb::network::HbServerOAuthStrategy;

#endif // HBSERVEROAUTHSTRATEGY_H
