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
    enum Service : serviceuid { SERVICE_QUESTION = hb::network::HbNetworkProtocol::SERVICE_USER + 1, SERVICE_MESSAGE };

    enum Code : codeuid {
        CODE_NONE = hb::network::HbNetworkProtocol::CODE_USER + 1,
        CODE_CLT_REQUEST,
        CODE_SRV_RESPONSE,
        CODE_SRV_MESSAGE
    };
};
} // namespace networkexample
} // namespace hb

#endif // PROTOCOL_H
