#ifndef HBPEER_H
#define HBPEER_H

/*! \file HbPeer.h */

// Qt
// Hb
// Local
#include <HbNetwork.h>
#include <config/peer/HbGeneralConfig.h>

namespace hb {
namespace network {
/*!
 * TODOC
 */
class HB_NETWORK_DECL HbPeer : public QObject {
    Q_OBJECT
    Q_DISABLE_COPY(HbPeer)

public:
    HbPeer() = delete;
    HbPeer(const HbGeneralConfig& config, QObject* parent = nullptr);
    virtual ~HbPeer() = default;

    virtual bool isReady() const;
    virtual bool leave() = 0;

private:
    bool mReady;
};
} // namespace network
} // namespace hb

#endif // HBSERVER_H
