/****************************************************************************
** Copyright (C) 2012-2015 Adrien Gavignet (hasboeuf)
** Contact: adrien.gavignet@gmail.com
**
** This file is part of the Hb module. Provided "AS IS", WITHOUT WARRANTIES
** OR CONDITIONS OF ANY KIND, either express or implied.
****************************************************************************/

#ifndef HBCOMPROTOCOL_H
#define HBCOMPROTOCOL_H

// Qt
#include <QtCore/QString>
// Hb
#include <HbGlobal.h>
#include <core/HbEnum.h>
// Local
#include <HbCom.h>

namespace hb
{
    namespace com
    {

        class HB_COM_DECL HbComProtocol final
        {
            Q_GADGET
            Q_ENUMS_HANDLER( HbComProtocol )
            Q_ENUMS( ComType )

        public:
            static QString msAppName;
            static quint16 msProtocolVersion;

            static const servuid SERVICE_UNDEFINED = 0;
            static const codeuid CODE_UNDEFINED    = 0;

            enum ComType : quint8
            {
                COM_UNDEFINED = 0,
                COM_TCP       = 1 << 0,
                COM_WEB       = 1 << 1,
                COM_SSL       = 1 << 2,
                COM_UDP       = 1 << 3,
                COM_LOCAL     = 1 << 4,
                COM_BLUETOOTH = 1 << 5
            };
            Q_META_ENUMS( ComType )
            Q_DECLARE_FLAGS( ComTypes, ComType )

            enum RoutingScheme : quint8
            {
                UNICAST = 0,
                MULTICAST = 1,
                BROADCAST = 2
            };
        };
    }
}

Q_DECLARE_OPERATORS_FOR_FLAGS( hb::com::HbComProtocol::ComTypes )

using hb::com::HbComProtocol;

#endif // HBCOMPROTOCOL_H
