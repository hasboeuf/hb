/****************************************************************************
** Copyright (C) 2012-2015 Adrien Gavignet (hasboeuf)
** Contact: adrien.gavignet@gmail.com
**
** This file is part of the Hb module. Provided "AS IS", WITHOUT WARRANTIES
** OR CONDITIONS OF ANY KIND, either express or implied.
****************************************************************************/

#ifndef HBCOMCONTRACT_H
#define HBCOMCONTRACT_H

// Qt
#include <QtCore/QObject>
#include <QtCore/QSharedPointer>
#include <QtCore/QSet>
#include <QtCore/QStringList>
// Hb
#include <HbGlobal.h>
#include <core/HbUId.h>
// Local
#include <HbCom.h>
#include <contract/HbComProtocol.h>
#include <contract/HbComHeader.h>

namespace hb
{
    namespace com
    {
        class HbComHeader;

        class HB_COM_DECL HbComContract : public HbUid< ctctuid, CLASS_CTCT >
        {
            Q_FRIEND_CLASS( HbComExchanges )

        public:
            virtual ~HbComContract();

            virtual void setHeader( const HbComHeader & header ) final;
            virtual const HbComHeader & header() const final;

            virtual void setSender( sockuid sender ) final;
            virtual sockuid sender() const final;

            virtual void addPendingReceiver( const QString & user_id ) final;

            virtual HbComProtocol::RoutingScheme routing() const final;
            virtual void setRouting( HbComProtocol::RoutingScheme routing ) final;

            virtual HbComContract * reply() const;
            virtual void updateReply() final;

            virtual const QString toString() const;

            virtual void setComType( HbComProtocol::ComType type ) final;
            virtual HbComProtocol::ComType networkType() const final;

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

            HbComContract();
            HbComContract( servuid service, codeuid code );
            HbComContract( const HbComContract & source );
            HbComContract & operator=( const HbComContract & source );

            virtual HbComContract * create() const = 0;

        private:
            virtual bool addSocketReceiver( sockuid receiver ) final ;
            virtual void resetSocketReceivers() final;

        protected:
            HbComHeader mHeader;
            HbComContract * mpReply;

        private:
            // Internal use. Server side. TODO protect the client side.
            sockuid mSender;
            HbComProtocol::ComType mComType;
            HbComProtocol::RoutingScheme mRouting;
            QSet< QString > mPendingReceivers; // user_id, morph into SocketReceivers at sending time.
            QSet< sockuid > mSocketReceivers;

        };

        typedef QSharedPointer< const HbComContract > ShConstHbComContract;
        typedef QSharedPointer< HbComContract >       ShHbComContract;
    }
}

using hb::com::HbComContract;

#endif // HBCOMCONTRACT_H
