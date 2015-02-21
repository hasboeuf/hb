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
#include <contract/HbComProtocol.h>
// Local


namespace hb
{
    namespace comexample
    {

        class Protocol
        {
        public:
            enum Service : servuid
            {
                SERVICE_NONE = HbComProtocol::SERVICE_UNDEFINED,
                SERVICE_QUESTION,
                SERVICE_MESSAGE
            };

            enum Code : codeuid
            {
                CODE_NONE = HbComProtocol::CODE_UNDEFINED,
                CODE_CLT_REQUEST,
                CODE_SRV_RESPONSE,
                CODE_SRV_MESSAGE
            };
        };
    }
}

#endif // PROTOCOL_H
