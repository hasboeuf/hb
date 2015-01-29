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
// Local
#include <HbNetwork.h>
#include <contract/HbNetworkProtocol.h>
#include <contract/HbNetworkHeader.h>

namespace hb
{
	namespace network
	{
        class HbNetworkHeader;

		class HB_NETWORK_DECL HbNetworkContract
        {
            Q_FRIEND_CLASS( HbNetworkExchanges )

		public:
            virtual ~HbNetworkContract() = default;

            virtual void setHeader( const HbNetworkHeader & header ) final;
            virtual const HbNetworkHeader & header() const final;

            virtual void addPendingReceiver( const QString & user_uuid ) final;
            virtual bool addReceiver( quint16 receiver ) final ;
            virtual void resetReceivers() final;

            virtual HbNetworkProtocol::RoutingScheme routing() const final;
            virtual void setRouting( HbNetworkProtocol::RoutingScheme routing ) final;

            virtual bool setReply( HbNetworkContract * reply ); // TODO DEL ?
            virtual HbNetworkContract * reply() const; // TODO = 0

            virtual void setNetworkType( HbNetworkProtocol::NetworkType type ) final;
            virtual HbNetworkProtocol::NetworkType networkType() const final;

            template< typename T >
            inline T * value() const final
			{
                return dynamic_cast< T * >( this );
            }

            virtual bool read( QDataStream & stream ) = 0;
            virtual bool write( QDataStream & stream ) const = 0;

		protected:

			HbNetworkContract() = delete;
            HbNetworkContract( HbNetworkProtocol::Service service, HbNetworkProtocol::Code code );
            HbNetworkContract( const HbNetworkContract & source );
            HbNetworkContract & operator=( const HbNetworkContract & source );

            virtual HbNetworkContract * create() const = 0;

		private:
            const QSet< sockuuid > & receivers() const;

        protected:
            HbNetworkHeader mHeader;

        private:
            HbNetworkContract * mpReply;

            // Internal use. Server side. TODO protect the client side.
            HbNetworkProtocol::NetworkType mNetworkType;
            HbNetworkProtocol::RoutingScheme mRouting;
            QSet< QString > mPendingReceivers; // user_uuid, morph into SocketReceivers at sending time.
            QSet< sockuuid > mSocketReceivers;

		};
	}
}

using hb::network::HbNetworkContract;

#endif // HBNETWORKCONTRACT_H
