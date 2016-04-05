/****************************************************************************
** Copyright (C) 2012-2015 Adrien Gavignet (hasboeuf)
** Contact: adrien.gavignet@gmail.com
**
** This file is part of the Hb module. Provided "AS IS", WITHOUT WARRANTIES
** OR CONDITIONS OF ANY KIND, either express or implied.
****************************************************************************/

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

namespace hb
{
    namespace network
    {
        /*!
         * TODOC
         */
        class HbNetworkHeader final
        {
            friend QDataStream & operator<<( QDataStream & stream, const HbNetworkHeader & header );
            friend QDataStream & operator>>( QDataStream & stream, HbNetworkHeader & header );

        public:

            HbNetworkHeader(); // Used before streamed back.
            HbNetworkHeader( const HbNetworkHeader & header );
            HbNetworkHeader( serviceuid service, codeuid code );
            HbNetworkHeader & operator=( const HbNetworkHeader & header );
            ~HbNetworkHeader() = default;

            QString toString() const;

            const QString & appName() const;
            quint16 protocolVersion() const;
            serviceuid service() const;
            codeuid code() const;

            void setRouting( HbNetworkProtocol::RoutingScheme routing );

        private:
            QString mAppName;
            quint16 mProtocolVersion;
            serviceuid mService;
            codeuid mCode;
        };

        QDataStream & operator<<(QDataStream & stream, const HbNetworkHeader & header);
        QDataStream & operator>>(QDataStream & stream, HbNetworkHeader & header);
    }
}

using hb::network::HbNetworkHeader;

#endif // HBNETWORKHEADER_H
