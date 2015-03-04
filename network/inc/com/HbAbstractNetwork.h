/****************************************************************************
** Copyright (C) 2012-2015 Adrien Gavignet (hasboeuf)
** Contact: adrien.gavignet@gmail.com
**
** This file is part of the Hb module. Provided "AS IS", WITHOUT WARRANTIES
** OR CONDITIONS OF ANY KIND, either express or implied.
****************************************************************************/

#ifndef HBABSTRACTNETWORK_H
#define HBABSTRACTNETWORK_H

// Qt
#include <QtNetwork/QAbstractSocket>
// Hb
#include <HbGlobal.h>
// Local
#include <HbNetwork.h>
#include <contract/HbNetworkContract.h>
#include <config/com/HbNetworkConfig.h>

namespace hb
{
    namespace network
    {

        class HB_NETWORK_DECL HbAbstractNetwork : public QObject
        {
            Q_OBJECT
            Q_DISABLE_COPY( HbAbstractNetwork )

        public:

            static bool checkHeader( const HbNetworkHeader & header );

            virtual bool join() = 0;
            virtual bool leave() = 0;
            virtual bool isReady() const = 0;
            virtual HbNetworkProtocol::NetworkType type() const = 0;

            virtual bool send( ShConstHbNetworkContract contract ) = 0; // TODO refresh

            virtual const HbNetworkConfig & configuration() const; // SUB

        protected:
            HbAbstractNetwork( QObject * parent = nullptr );
            virtual ~HbAbstractNetwork() = default;

        private:
            HbNetworkConfig mConfig; // SUB
        };
    }
}

#endif // HBABSTRACTNETWORK_H
