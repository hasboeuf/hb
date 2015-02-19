/****************************************************************************
** Copyright (C) 2012-2015 Adrien Gavignet (hasboeuf)
** Contact: adrien.gavignet@gmail.com
**
** This file is part of the Hb module. Provided "AS IS", WITHOUT WARRANTIES
** OR CONDITIONS OF ANY KIND, either express or implied.
****************************************************************************/

#ifndef HBNETWORKHEADER_H
#define HBNETWORKHEADER_H

// Hb
#include <HbGlobal.h>
// Local
#include <HbNetwork.h>
#include <contract/HbNetworkProtocol.h>

namespace hb
{
    namespace network
    {

        class HbNetworkHeader final
        {
            friend QDataStream & operator<<( QDataStream & stream, const HbNetworkHeader & header );
            friend QDataStream & operator>>( QDataStream & stream, HbNetworkHeader & header );

        public:

            HbNetworkHeader(); // Used before streamed back.
            HbNetworkHeader( const HbNetworkHeader & header );
            HbNetworkHeader( HbNetworkProtocol::Service service, HbNetworkProtocol::Code code );
            HbNetworkHeader & operator=( const HbNetworkHeader & header );
            ~HbNetworkHeader() = default;

            const QString & appName() const;
            quint16 protocolVersion() const;
            HbNetworkProtocol::Service service() const;
            HbNetworkProtocol::Code code() const;

            void setRouting( HbNetworkProtocol::RoutingScheme routing );

        private:
            QString mAppName;
            quint16 mProtocolVersion;
            HbNetworkProtocol::Service mService;
            HbNetworkProtocol::Code mCode;
        };

        HB_NETWORK_DECL QDataStream & operator<<(QDataStream & stream, const HbNetworkHeader & header);
        HB_NETWORK_DECL QDataStream & operator>>(QDataStream & stream, HbNetworkHeader & header);
    }
}

using hb::network::HbNetworkHeader;

#endif // HBNETWORKHEADER_H
