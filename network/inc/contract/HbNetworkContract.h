/****************************************************************************
** Copyright (C) 2012-2015 Adrien Gavignet (hasboeuf)
** Contact: adrien.gavignet@gmail.com
**
** This file is part of the Hb module. Provided "AS IS", WITHOUT WARRANTIES
** OR CONDITIONS OF ANY KIND, either express or implied.
****************************************************************************/

#ifndef HBNETWORKCONTRACT_H
#define HBNETWORKCONTRACT_H

// Qt
#include <QtCore/QObject>
#include <QtCore/QSet>
#include <QtCore/QStringList>
// Hb
#include <HbGlobal.h>
#include <core/HbUId.h>
// Local
#include <HbNetwork.h>
#include <contract/HbNetworkProtocol.h>
#include <contract/HbNetworkHeader.h>

namespace hb
{
	namespace network
	{
        class HbNetworkHeader;

        class HB_NETWORK_DECL HbNetworkContract : public HbUid< ctctuid, CLASS_CTCT >
        {
            Q_FRIEND_CLASS( HbNetworkExchanges )

		public:
            virtual ~HbNetworkContract() = default;

            virtual void setHeader( const HbNetworkHeader & header ) final;
            virtual const HbNetworkHeader & header() const final;

            virtual void setSender( sockuid sender ) final;
            virtual sockuid sender() const final;

            virtual void addPendingReceiver( const QString & user_id ) final;

            virtual HbNetworkProtocol::RoutingScheme routing() const final;
            virtual void setRouting( HbNetworkProtocol::RoutingScheme routing ) final;

            virtual HbNetworkContract * reply() const;

            virtual void setNetworkType( HbNetworkProtocol::NetworkType type ) final;
            virtual HbNetworkProtocol::NetworkType networkType() const final;

            template< typename T >
            inline const T * value() const final
			{
                return dynamic_cast< const T * >( this );
            }

            template< typename T >
            inline T * value() final
            {
                return dynamic_cast< T * >( this );
            }

            virtual bool read( QDataStream & stream ) = 0;
            virtual bool write( QDataStream & stream ) const = 0;

            const QSet< sockuid > & socketReceivers() const;
            sockuid socketReceiver() const;

		protected:

            HbNetworkContract();
            HbNetworkContract( HbNetworkProtocol::Service service, HbNetworkProtocol::Code code );
            HbNetworkContract( const HbNetworkContract & source );
            HbNetworkContract & operator=( const HbNetworkContract & source );

            virtual HbNetworkContract * create() const = 0;

            virtual void setReply( HbNetworkContract * reply ) final;

        private:
            virtual bool addSocketReceiver( sockuid receiver ) final ;
            virtual void resetSocketReceivers() final;

        protected:
            HbNetworkHeader mHeader;
            HbNetworkContract * mpReply;

        private:
            // Internal use. Server side. TODO protect the client side.
            sockuid mSender;
            HbNetworkProtocol::NetworkType mNetworkType;
            HbNetworkProtocol::RoutingScheme mRouting;
            QSet< QString > mPendingReceivers; // user_id, morph into SocketReceivers at sending time.
            QSet< sockuid > mSocketReceivers;

		};
	}
}

using hb::network::HbNetworkContract;

#endif // HBNETWORKCONTRACT_H
