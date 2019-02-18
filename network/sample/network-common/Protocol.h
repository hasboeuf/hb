#ifndef PROTOCOL_H
#define PROTOCOL_H

// Qt
// Hb
#include <contract/HbNetworkProtocol.h>
// Local

namespace hb {
namespace networkexample {

class Protocol {
public:
    enum Channel : serviceuid { CHANNEL_CHAT = hb::network::HbNetworkProtocol::SERVICE_USER + 1, CHANNEL_SUM };

    enum Code : codeuid {
        CODE_NONE = hb::network::HbNetworkProtocol::CODE_USER + 1,
        CODE_CLT_CHAT_MESSAGE,
        CODE_SRV_CHAT_MESSAGE,
        CODE_CLT_REQUEST_SUM,
        CODE_SRV_RESPONSE_SUM
    };
};
} // namespace networkexample
} // namespace hb

#endif // PROTOCOL_H
