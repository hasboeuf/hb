/****************************************************************************
** Copyright (C) 2012-2015 Adrien Gavignet (hasboeuf)
** Contact: adrien.gavignet@gmail.com
**
** This file is part of the Hb module. Provided "AS IS", WITHOUT WARRANTIES
** OR CONDITIONS OF ANY KIND, either express or implied.
****************************************************************************/

#ifndef HBCOMEXCHANGES_H
#define HBCOMEXCHANGES_H

// Qt
#include <QtCore/QIODevice>
// Hb
#include <HbGlobal.h>
// Local
#include <HbCom.h>
#include <contract/HbComContract.h>

namespace hb
{
    namespace com
    {
        class HB_COM_DECL HbComExchanges final
        {
            Q_FRIEND_CLASS( HbComConfig )

        protected:
            HbComExchanges() = default;
            virtual ~HbComExchanges();
            HbComExchanges & operator=( const HbComExchanges & source );

        public:
            template< typename T >
            inline bool plug()
            {
                T * reference = q_check_ptr( new T() );
                HbComContract * contract = dynamic_cast< HbComContract * >( reference );
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
                HbComContract * contract = dynamic_cast< HbComContract * >( reference );
                if( !contract )
                {
                    return false;
                }
                return remove( reference );
            }

            bool registered( servuid service, codeuid code ) const;
            HbComContract * contract( const HbComHeader & header ) const;

        private:
            bool add( HbComContract * contract );
            bool remove( HbComContract * contract );

        private:
            typedef QHash< codeuid, HbComContract * > Contracts;
            QHash< servuid, Contracts > mContracts;
        };
    }
}

using hb::com::HbComExchanges;

#endif // HBCOMEXCHANGES_H
