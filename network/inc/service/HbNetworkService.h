/****************************************************************************
** Copyright (C) 2012-2015 Adrien Gavignet (hasboeuf)
** Contact: adrien.gavignet@gmail.com
**
** This file is part of the Hb module. Provided "AS IS", WITHOUT WARRANTIES
** OR CONDITIONS OF ANY KIND, either express or implied.
****************************************************************************/

#ifndef HBNETWORKSERVICE_H
#define HBNETWORKSERVICE_H

/*! \file HbNetworkService.h */

// Qt
#include <QtCore/QObject>
// Hb
// Local
#include <HbNetwork.h>
#include <user/HbNetworkUserData.h>
#include <contract/HbNetworkContract.h>
#include <contract/HbNetworkExchanges.h>
#include <listener/IHbContractListener.h>

namespace hb
{
    namespace network
    {
        /*!
         * TODOC
         */
        class HB_NETWORK_DECL HbNetworkService : public QObject
        {
            Q_OBJECT

        public:

            HbNetworkService() = default;
            virtual ~HbNetworkService(){} //!< \todo defaulted linux-g++ issue

            virtual void reset() = 0;
            virtual HbNetworkProtocol::NetworkTypes enabledNetworkTypes() const = 0;
            virtual void plugContracts( HbNetworkExchanges & exchanges ) = 0;

            virtual serviceuid uid() const = 0;

        public callbacks:

        signals:
            void userContractToSend  ( HbNetworkUserData & user_data, HbNetworkContract * contract );
            void readyContractToSend ( const HbNetworkContract * contract );

            // Only used in server side.
            void userToKick  ( HbNetworkUserData & user_data, netwint reason, const QString & description = QString() );
            void socketToKick( networkuid socket_uid, netwint reason, const QString & description = QString() );

        };
    }
}

#endif // HBNETWORKSERVICE_H
