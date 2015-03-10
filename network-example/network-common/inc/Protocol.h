/****************************************************************************
** Copyright (C) 2012-2015 Adrien Gavignet (hasboeuf)
** Contact: adrien.gavignet@gmail.com
**
** This file is part of the Hb module. Provided "AS IS", WITHOUT WARRANTIES
** OR CONDITIONS OF ANY KIND, either express or implied.
****************************************************************************/

#ifndef PROTOCOL_H
#define PROTOCOL_H

// Qt
// Hb
#include <contract/HbNetworkProtocol.h>
// Local


namespace hb
{
    namespace networkexample
    {

        class Protocol
        {
        public:
            enum Service : serviceuid
            {
                SERVICE_CHAT = hb::network::HbNetworkProtocol::SERVICE_USER,
                SERVICE_MATH_OPERATION
            };

            enum Code : codeuid
            {
                CODE_NONE = hb::network::HbNetworkProtocol::CODE_USER,
                CODE_CLT_CHAT_MESSAGE,
                CODE_SRV_CHAT_MESSAGE,
                CODE_CLT_REQUEST_SUM,
                CODE_SRV_RESPONSE_SUM
            };
        };
    }
}

#endif // PROTOCOL_H
