#ifndef HBABSTRACTNETWORK_H
#define HBABSTRACTNETWORK_H

/*! \file HbAbstractNetwork.h */

// Qt
#include <QtNetwork/QAbstractSocket>
// Hb
#include <HbGlobal.h>
// Local
#include <HbNetwork.h>
#include <config/com/HbNetworkConfig.h>
#include <contract/HbNetworkContract.h>

namespace hb {
namespace network {
/*!
 * TODOC
 */
class HB_NETWORK_DECL HbAbstractNetwork : public QObject {
    Q_OBJECT
    Q_DISABLE_COPY(HbAbstractNetwork)

public:
    static bool checkHeader(const HbNetworkHeader& header);

    virtual bool join() = 0;
    virtual bool leave() = 0;
    virtual bool isReady() const = 0;
    virtual HbNetworkProtocol::NetworkType type() const = 0;

    virtual bool send(ShConstHbNetworkContract contract) = 0;

    virtual const HbNetworkConfig& configuration() const; // SUB

protected:
    HbAbstractNetwork(QObject* parent = nullptr);
    virtual ~HbAbstractNetwork() = default;

    virtual bool connectToNetwork() = 0;
    virtual void disconnectFromNetwork() = 0;

private:
    HbNetworkConfig mConfig; // SUB
};
} // namespace network
} // namespace hb

#endif // HBABSTRACTNETWORK_H
