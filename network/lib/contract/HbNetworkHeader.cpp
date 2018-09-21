// Qt
// Local
#include <contract/HbNetworkHeader.h>

using namespace hb::network;

HbNetworkHeader::HbNetworkHeader() {
    mAppName = HbNetworkProtocol::msAppName;
    mProtocolVersion = HbNetworkProtocol::msProtocolVersion;
    mService = HbNetworkProtocol::SERVICE_UNDEFINED;
    mCode = HbNetworkProtocol::CODE_UNDEFINED;
}

HbNetworkHeader::HbNetworkHeader(serviceuid service, codeuid code) : HbNetworkHeader() {
    mService = service;
    mCode = code;
}

HbNetworkHeader::HbNetworkHeader(const HbNetworkHeader& header) {
    if (&header != this) {
        mAppName = header.mAppName;
        mProtocolVersion = header.mProtocolVersion;
        mService = header.mService;
        mCode = header.mCode;
    }
}

HbNetworkHeader& HbNetworkHeader::operator=(const HbNetworkHeader& header) {
    if (&header != this) {
        mAppName = header.mAppName;
        mProtocolVersion = header.mProtocolVersion;
        mService = header.mService;
        mCode = header.mCode;
    }
    return *this;
}

QString HbNetworkHeader::toString() const {
    return QString("app=%1,protocol=%2,service=%3,code=%4")
        .arg(mAppName)
        .arg(mProtocolVersion)
        .arg(HbNetworkProtocol::MetaService::toString(mService))
        .arg(HbNetworkProtocol::MetaCode::toString(mCode));
}

const QString& HbNetworkHeader::appName() const {
    return mAppName;
}

quint16 HbNetworkHeader::protocolVersion() const {
    return mProtocolVersion;
}

serviceuid HbNetworkHeader::service() const {
    return mService;
}

codeuid HbNetworkHeader::code() const {
    return mCode;
}

namespace hb {
namespace network {

QDataStream& operator<<(QDataStream& stream, const HbNetworkHeader& header) {
    stream << header.mAppName;
    stream << header.mProtocolVersion;
    stream << header.mService;
    stream << header.mCode;

    return stream;
}

QDataStream& operator>>(QDataStream& stream, HbNetworkHeader& header) {
    stream >> header.mAppName;
    stream >> header.mProtocolVersion;
    stream >> header.mService;
    stream >> header.mCode;

    return stream;
}
} // namespace network
} // namespace hb
