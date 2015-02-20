/****************************************************************************
** Copyright (C) 2012-2015 Adrien Gavignet (hasboeuf)
** Contact: adrien.gavignet@gmail.com
**
** This file is part of the Hb module. Provided "AS IS", WITHOUT WARRANTIES
** OR CONDITIONS OF ANY KIND, either express or implied.
****************************************************************************/

#ifndef HBCOMHEADER_H
#define HBCOMHEADER_H

// Hb
#include <HbGlobal.h>
// Local
#include <HbCom.h>
#include <contract/HbComProtocol.h>

namespace hb
{
    namespace com
    {

        class HbComHeader final
        {
            friend QDataStream & operator<<( QDataStream & stream, const HbComHeader & header );
            friend QDataStream & operator>>( QDataStream & stream, HbComHeader & header );

        public:

            HbComHeader(); // Used before streamed back.
            HbComHeader( const HbComHeader & header );
            HbComHeader( servuid service, codeuid code );
            HbComHeader & operator=( const HbComHeader & header );
            ~HbComHeader() = default;

            const QString & appName() const;
            quint16 protocolVersion() const;
            servuid service() const;
            codeuid code() const;

            void setRouting( HbComProtocol::RoutingScheme routing );

        private:
            QString mAppName;
            quint16 mProtocolVersion;
            servuid mService;
            codeuid mCode;
        };

        HB_COM_DECL QDataStream & operator<<(QDataStream & stream, const HbComHeader & header);
        HB_COM_DECL QDataStream & operator>>(QDataStream & stream, HbComHeader & header);
    }
}

using hb::com::HbComHeader;

#endif // HBCOMHEADER_H
