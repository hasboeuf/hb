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
                SERVICE_QUESTION = hb::network::HbNetworkProtocol::SERVICE_USER,
                SERVICE_MESSAGE
            };

            enum Code : codeuid
            {
                CODE_NONE = hb::network::HbNetworkProtocol::CODE_USER,
                CODE_CLT_REQUEST,
                CODE_SRV_RESPONSE,
                CODE_SRV_MESSAGE
            };
        };
    }
}

#endif // PROTOCOL_H
