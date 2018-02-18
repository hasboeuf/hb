/****************************************************************************
** Copyright (C) 2012-2015 Adrien Gavignet (hasboeuf)
** Contact: adrien.gavignet@gmail.com
**
** This file is part of the Hb module. Provided "AS IS", WITHOUT WARRANTIES
** OR CONDITIONS OF ANY KIND, either express or implied.
****************************************************************************/

#ifndef HBENUM_H
#define HBENUM_H

/*! \file HbEnum.h */

// Hb
#include <HbTools.h>
#include <core/HbEnumerator.h>

namespace hbprivate
{
    /*!
     * Internal class, TODOC.
     */
    template< typename Class, typename Enum >
    class HbEnumHelper
    {
        Q_DEFAULT_COPY( HbEnumHelper )


    public:

        static QString name()
        {
            return hbprivate::HbEnumerator< Class >::template name< Enum >();
        }

        static qint16 count()
        {
            return hbprivate::HbEnumerator< Class >::template count< Enum >();
        }

        static bool isFlag()
        {
            return hbprivate::HbEnumerator< Class >::template isFlag< Enum >();
        }

        static nullable< Enum > value( qint16 index )
        {
            return hbprivate::HbEnumerator< Class >::template value< Enum >( index );
        }

        static qint16 index( Enum value )
        {
            return hbprivate::HbEnumerator< Class >::index( value );
        }

        static QString toString( Enum value )
        {
            QString texte = hbprivate::HbEnumerator< Class >::toString( value );
            if( texte.isEmpty() )
            {
                texte = QString::number( ( int ) value );
            }
            return texte;
        }

        static QString toString( qint64 value )
        {
            return toString( ( Enum ) value );
        }

        static QStringList toString()
        {
            return hbprivate::HbEnumerator< Class >::template toString< Enum >();
        }

        static nullable< Enum > fromString( const QString & label )
        {
            return hbprivate::HbEnumerator< Class >::template fromString< Enum >( label );
        }

        static Enum fromString( const QString & label, Enum defaultValue )
        {
            return hbprivate::HbEnumerator< Class >::template fromString< Enum >( label ).value( defaultValue );
        }
    };
}

/*! \def Q_ENUMS_HANDLER
 * Q_ENUMS_HANDLER enables introspection of enums class.
 */
#define Q_ENUMS_HANDLER( Class ) \
public: \
\
    template< typename Enum > \
    class HbEnum : public hbprivate::HbEnumHelper< Class, Enum > {}; \
\
private:

#define Q_META_ENUMS( Enum ) \
    typedef HbEnum< Enum > Meta ## Enum;

#endif