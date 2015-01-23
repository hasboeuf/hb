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
			Q_GADGET
            Q_FRIEND_CLASS( HbNetworkExchanges )

		public:

            const HbNetworkHeader & header() const;

            virtual void addPendingReceiver( const QString & user_uuid );
            virtual bool addReceiver( quint16 receiver );
			virtual void resetReceivers();

            virtual bool setReply( HbNetworkContract * reply );
			virtual HbNetworkContract * reply() const;

            template< typename T >
            inline T * value() const
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
			virtual ~HbNetworkContract() = default;

            virtual HbNetworkContract * copy() const = 0;

		private:
			const QSet< quint16 > & receivers() const;

        protected:
            HbNetworkHeader mHeader;

        private:
            // Internal use.
            HbNetworkProtocol::NetworkType mNetworkTarget;
            QSet< QString > mPendingReceivers; // user_uuid, morph into SocketReceivers at sending time.
            QSet< quint16 > mSocketReceivers;
            HbNetworkContract * mpReply;
		};
	}
}

using hb::network::HbNetworkContract;

#endif // HBNETWORKCONTRACT_H
