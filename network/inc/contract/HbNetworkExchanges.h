/****************************************************************************
** Copyright (C) 2012-2015 Adrien Gavignet (hasboeuf)
** Contact: adrien.gavignet@gmail.com
**
** This file is part of the Hb module. Provided "AS IS", WITHOUT WARRANTIES
** OR CONDITIONS OF ANY KIND, either express or implied.
****************************************************************************/

#ifndef HBNETWORKEXCHANGES_H
#define HBNETWORKEXCHANGES_H

// Qt
#include <QtCore/QIODevice>
// Hb
#include <HbGlobal.h>
// Local
#include <HbNetwork.h>
#include <contract/HbNetworkContract.h>

namespace hb
{
	namespace network
	{
        class HB_NETWORK_DECL HbNetworkExchanges final
        {
            Q_FRIEND_CLASS( HbNetworkConfig )

        protected:
            HbNetworkExchanges() = default;
            virtual ~HbNetworkExchanges();
            HbNetworkExchanges & operator=( const HbNetworkExchanges & source );

        public:
            template< typename T >
            inline bool plug()
            {
                T * reference = q_check_ptr( new T() );
                HbNetworkContract * contract = dynamic_cast< HbNetworkContract * >( reference );
                if( !contract )
                {
                    return false;
                }

                return add( reference );
            }

            template< typename T >
            inline bool unplug()
            {
                T * reference = q_check_ptr( new T() );
                HbNetworkContract * contract = dynamic_cast< HbNetworkContract * >( reference );
                if( !contract )
                {
                    return false;
                }
                return remove( reference );
            }

            bool registered(HbNetworkContract::Service service, HbNetworkContract::Code code) const;
            HbNetworkContract * contract( HbNetworkContract::Service service, HbNetworkContract::Code code ) const;

        private:
            bool add( HbNetworkContract * contract );
            bool remove( HbNetworkContract * contract );

        private:
            typedef QHash< HbNetworkContract::Code, HbNetworkContract * > Contracts;
            QHash< HbNetworkContract::Service, Contracts > _contracts;
        };
	}
}

using hb::network::HbNetworkExchanges;

#endif // HBNETWORKEXCHANGES_H
