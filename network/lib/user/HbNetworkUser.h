/****************************************************************************
** Copyright (C) 2012-2015 Adrien Gavignet (hasboeuf)
** Contact: adrien.gavignet@gmail.com
**
** This file is part of the Hb module. Provided "AS IS", WITHOUT WARRANTIES
** OR CONDITIONS OF ANY KIND, either express or implied.
****************************************************************************/

#ifndef HBNETWORKUSER_H
#define HBNETWORKUSER_H

/*! \file HbNetworkUser.h */

// Qt
#include <QtCore/QObject>
#include <QtCore/QSet>
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
        class HB_NETWORK_DECL HbNetworkUser : public QObject
        {
            Q_OBJECT
        public:

            HbNetworkUser();
            virtual ~HbNetworkUser( ) = default;

            virtual void reset();

            ShConstHbNetworkUserInfo & info();
            void setInfo( const HbNetworkUserInfo & info );

            networkuid mainSocketUid() const;

            virtual void delSocket( networkuid socket_uid ) = 0;
            virtual QList< networkuid > socketsUid() const  = 0;

        protected:
            networkuid mMainSocket;

        private:
            ShConstHbNetworkUserInfo mInfo;

        };
    }
}

#endif // HBNETWORKUSER_H
