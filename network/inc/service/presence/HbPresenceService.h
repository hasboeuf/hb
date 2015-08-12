/****************************************************************************
** Copyright (C) 2012-2015 Adrien Gavignet (hasboeuf)
** Contact: adrien.gavignet@gmail.com
**
** This file is part of the Hb module. Provided "AS IS", WITHOUT WARRANTIES
** OR CONDITIONS OF ANY KIND, either express or implied.
****************************************************************************/

#ifndef HBPRESENCESERVICE_H
#define HBPRESENCESERVICE_H

/*! \file HbPresenceService.h */

// Qt
// Hb
// Local
#include <service/HbNetworkService.h>
#include <listener/IHbSocketAuthListener.h>

namespace hb
{
    namespace network
    {
        /*!
         * TODOC
         */
        class HB_NETWORK_DECL HbPresenceService : public HbNetworkService, public IHbSocketAuthListener
        {
        public:

            HbPresenceService();
            virtual ~HbPresenceService(){} //!< \todo defaulted linux-g++ issue

            virtual HbNetworkProtocol::NetworkTypes enabledNetworkTypes() const override;
            virtual void plugContracts( HbNetworkExchanges & exchanges ) override;

            virtual serviceuid uid() const override;

        public callbacks:

        };
    }
}

#endif // HBPRESENCESERVICE_H
