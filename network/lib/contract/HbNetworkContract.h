/****************************************************************************
** Copyright (C) 2012-2015 Adrien Gavignet (hasboeuf)
** Contact: adrien.gavignet@gmail.com
**
** This file is part of the Hb module. Provided "AS IS", WITHOUT WARRANTIES
** OR CONDITIONS OF ANY KIND, either express or implied.
****************************************************************************/

#ifndef HBNETWORKCONTRACT_H
#define HBNETWORKCONTRACT_H

/*! \file HbNetworkContract.h */

// Qt
#include <QtCore/QObject>
#include <QtCore/QSharedPointer>
#include <QtCore/QSet>
#include <QtCore/QStringList>
// Hb
#include <HbGlobal.h>
#include <core/HbUid.h>
// Local
#include <HbNetwork.h>
#include <contract/HbNetworkProtocol.h>
#include <contract/HbNetworkHeader.h>
#include <user/HbNetworkUserInfo.h>

namespace hb
{
    namespace network
    {
        /*!
         * TODOC
         */
        class HB_NETWORK_DECL HbNetworkContract : public HbUid< CLASS_CONTRACT >
        {
            Q_FRIEND_CLASS( HbNetworkExchanges )

        public:
            virtual ~HbNetworkContract();

            virtual bool isValid() const final;

            virtual void setHeader( const HbNetworkHeader & header ) final;
            virtual const HbNetworkHeader & header() const final;

            virtual void setSender( networkuid sender ) final;
            virtual networkuid sender() const final;

            virtual void addPendingReceiver( ShConstHbNetworkUserInfo users_infos ) final;
            virtual void addSocketReceiver ( networkuid socket_uid ) final;
            virtual const QList< ShConstHbNetworkUserInfo > & pendingReceivers() const final;
            virtual const QSet< networkuid > & receivers() const final;
            virtual networkuid receiver() const final;

            virtual void setNetworkReceiver( networkuid network_receiver ) final;
            virtual networkuid networkReceiver() const;

            virtual HbNetworkProtocol::RoutingScheme routing() const final;
            virtual bool setRouting( HbNetworkProtocol::RoutingScheme routing ) final;

            virtual HbNetworkContract * takeReply() const;
            virtual void updateReply() final;

            virtual QString toString() const;

            virtual void setNetworkType( HbNetworkProtocol::NetworkType type ) final;
            virtual HbNetworkProtocol::NetworkType networkType() const final;

            template< typename T >
            inline const T * value() const
            {
                return dynamic_cast< const T * >( this );
            }

            template< typename T >
            inline T * value()
            {
                return dynamic_cast< T * >( this );
            }

            virtual bool read( QDataStream & stream ) = 0;
            virtual bool write( QDataStream & stream ) const = 0;

        protected:

            HbNetworkContract();
            HbNetworkContract( serviceuid service, codeuid code );
            HbNetworkContract( const HbNetworkContract & source );
            HbNetworkContract & operator=( const HbNetworkContract & source );

            virtual HbNetworkContract * create() const = 0;

        protected:
            HbNetworkHeader mHeader;
            HbNetworkContract * mpReply;

        private:
            void resetReceivers();

        private:
            //! \todo Internal use. Server side. Protect the client side.
            networkuid mSender;
            HbNetworkProtocol::NetworkType mNetworkType;
            HbNetworkProtocol::RoutingScheme mRouting;

            QList< ShConstHbNetworkUserInfo > mPendingReceivers; // Users infos, morph into networkuid at sending time.
            QSet< networkuid > mReceivers;

            networkuid mNetworkReceiver; // Used by server channels.
        };

        typedef QSharedPointer< const HbNetworkContract > ShConstHbNetworkContract;
        typedef QSharedPointer< HbNetworkContract >       ShHbNetworkContract;
    }
}

using hb::network::HbNetworkContract;

#endif // HBNETWORKCONTRACT_H
