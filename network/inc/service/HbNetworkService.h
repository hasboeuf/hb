/****************************************************************************
** Copyright (C) 2012-2015 Adrien Gavignet (hasboeuf)
** Contact: adrien.gavignet@gmail.com
**
** This file is part of the Hb module. Provided "AS IS", WITHOUT WARRANTIES
** OR CONDITIONS OF ANY KIND, either express or implied.
****************************************************************************/

#ifndef HBNETWORKSERVICE_H
#define HBNETWORKSERVICE_H

// Qt
#include <QtCore/QObject>
// Hb
// Local
#include <HbNetwork.h>
#include <user/HbNetworkUserInfo.h>
#include <contract/HbNetworkContract.h>
#include <contract/HbNetworkExchanges.h>
#include <listener/IHbContractListener.h>

namespace hb
{
    namespace network
    {

        class HB_NETWORK_DECL HbNetworkService : public QObject, public IHbContractListener
        {
            Q_OBJECT

        public:

            HbNetworkService() = default;
            virtual ~HbNetworkService() = default;

            virtual HbNetworkProtocol::NetworkTypes enabledNetworkTypes() const = 0;
            virtual void plugContracts( HbNetworkExchanges & exchanges ) = 0;

            virtual serviceuid id() const final
            {
                return mId;
            }

        public callbacks:
            virtual void onContractReceived( const HbNetworkContract * contract ) = 0;

        signals:
            //void socketContractToSend( networkuid receiver, HbNetworkContract * contract );
            //void userContractToSend  ( const HbNetworkUserInfo & user, HbNetworkContract * contract );
            void readyContractToSend ( const HbNetworkContract * contract );

            // Only used in server side.
            void userToKick  ( const HbNetworkUserInfo &user_info, netwint reason, const QString & description = QString() );
            void socketToKick( networkuid socket_uid, netwint reason, const QString & description = QString() );

        protected:
            serviceuid mId = HbNetworkProtocol::SERVICE_UNDEFINED;
        };
    }
}

#endif // HBNETWORKSERVICE_H
