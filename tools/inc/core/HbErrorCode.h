/****************************************************************************
** Copyright (C) 2012-2015 Adrien Gavignet (hasboeuf)
** Contact: adrien.gavignet@gmail.com
**
** This file is part of the Hb module. Provided "AS IS", WITHOUT WARRANTIES
** OR CONDITIONS OF ANY KIND, either express or implied.
****************************************************************************/

#ifndef HBERRORCODE_H
#define HBERRORCODE_H

/*! \file HbErrorCode.h */

// Qt
#include <QtCore/QHash>
// Local
#include <HbTools.h>
#include <HbGlobal.h>

namespace hb
{
    namespace tools
    {

        /*!
         * TODOC
         */
        class HB_TOOLS_DECL HbErrorCode final
        {
            Q_DEFAULT_COPY( HbErrorCode )


        public :

            HbErrorCode() = default;
            virtual ~HbErrorCode() = default;

            template< typename T >
            inline QString operator ()( T code ) const
            {
                return get( ( qint32 ) code );
            }

            template< typename T >
            inline bool add( T code, const char * message, ... )
            {
                bool status = false;

                if( message )
                {
                    va_list args;
                    va_start( args, message );
                    status = add( ( qint32 ) code, QString().vsprintf( message, args ) );
                    va_end( args );
                }

                return status;
            }

        private :

            bool add( qint32 code, const QString & message );
            QString get( qint32 code ) const;


        private :

            QHash< qint32, QString > mErrors;
        };
    }
}

#endif // HBERRORCODE_H
