#ifndef HBNETWORKHEADER_H
#define HBNETWORKHEADER_H

/*! \file HbNetworkHeader.h */

// Qt
#include <QtCore/QDataStream>
// Hb
#include <HbGlobal.h>
// Local
#include <HbNetwork.h>
#include <contract/HbNetworkProtocol.h>

namespace hb {
namespace network {
/*!
 * TODOC
 */
class HbNetworkHeader {
    friend QDataStream& operator<<(QDataStream& stream, const HbNetworkHeader& header);
    friend QDataStream& operator>>(QDataStream& stream, HbNetworkHeader& header);

public:
    HbNetworkHeader(); // Used before streamed back.
    HbNetworkHeader(const HbNetworkHeader& header);
    HbNetworkHeader(serviceuid service, codeuid code);
    HbNetworkHeader& operator=(const HbNetworkHeader& header);
    ~HbNetworkHeader() = default;

    QString toString() const;

    QString appName() const;
    quint16 protocolVersion() const;
    serviceuid service() const;
    codeuid code() const;

    void setRouting(HbNetworkProtocol::RoutingScheme routing);

private:
    QString mAppName;
    quint16 mProtocolVersion;
    serviceuid mService;
    codeuid mCode;
};

QDataStream& operator<<(QDataStream& stream, const HbNetworkHeader& header);
QDataStream& operator>>(QDataStream& stream, HbNetworkHeader& header);
} // namespace network
} // namespace hb

using hb::network::HbNetworkHeader;

#endif // HBNETWORKHEADER_H
