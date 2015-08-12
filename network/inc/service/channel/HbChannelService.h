/****************************************************************************
** Copyright (C) 2012-2015 Adrien Gavignet (hasboeuf)
** Contact: adrien.gavignet@gmail.com
**
** This file is part of the Hb module. Provided "AS IS", WITHOUT WARRANTIES
** OR CONDITIONS OF ANY KIND, either express or implied.
****************************************************************************/

#ifndef HBCHANNELSERVICE_H
#define HBCHANNELSERVICE_H

/*! \file HbChannelService.h */

// Qt
#include <QtCore/QHash>
// Hb
// Local
#include <service/HbNetworkService.h>
#include <listener/IHbUserListener.h>
#include <listener/IHbUserContractListener.h>

namespace hb
{
    namespace network
    {
        class HbNetworkChannel;

        /*!
         * TODOC
         */
        class HB_NETWORK_DECL HbChannelService : public HbNetworkService, public IHbUserListener, public IHbUserContractListener
        {
        public:

            HbChannelService();
            virtual ~HbChannelService() = default;

            virtual HbNetworkProtocol::NetworkTypes enabledNetworkTypes() const override;

            virtual serviceuid uid() const override;

            virtual bool addChannel( HbNetworkChannel * channel );
            virtual HbNetworkChannel * channel( serviceuid channel_uid );

        public callbacks:

        signals:
            void userContractToSend( const HbNetworkUserData & user_data, HbNetworkContract * contract );

        private:
            QHash< serviceuid, HbNetworkChannel * > mChannels;
        };
    }
}

#endif // HBCHANNELSERVICE_H
