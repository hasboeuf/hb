/****************************************************************************
** Copyright (C) 2012-2015 Adrien Gavignet (hasboeuf)
** Contact: adrien.gavignet@gmail.com
**
** This file is part of the Hb module. Provided "AS IS", WITHOUT WARRANTIES
** OR CONDITIONS OF ANY KIND, either express or implied.
****************************************************************************/

#ifndef HBNETWORKUSERDATA_H
#define HBNETWORKUSERDATA_H

/*! \file HbNetworkUser.h */

// Qt
// Hb
// Local
#include <HbNetwork.h>
#include <user/HbNetworkUserInfo.h>
#include <contract/HbNetworkProtocol.h>

namespace hb
{
    namespace network
    {
        /*!
         * TODOC
         */
        class HB_NETWORK_DECL HbNetworkUserData
        {
            friend class HbNetworkUser;

        public:
            HbNetworkUserData();
            virtual ~HbNetworkUserData() = default;
            HbNetworkUserData( const HbNetworkUserData & source );
            HbNetworkUserData & operator=( const HbNetworkUserData & source );

            const HbNetworkUserInfo * info() const;
            void setInfo( ShConstHbNetworkUserInfo & info );

            networkuid socketUid() const;

        protected:
            void setSocketUid( networkuid socket_uid ); // Used by HbNetworkUser.

        private:
            networkuid mSocketUid;
            ShConstHbNetworkUserInfo mInfo;
        };
    }
}

using hb::network::HbNetworkUserData;

#endif // HBNETWORKUSERDATA_H
