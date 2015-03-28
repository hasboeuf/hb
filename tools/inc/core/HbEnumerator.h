/****************************************************************************
** Copyright (C) 2012-2015 Adrien Gavignet (hasboeuf)
** Contact: adrien.gavignet@gmail.com
**
** This file is part of the Hb module. Provided "AS IS", WITHOUT WARRANTIES
** OR CONDITIONS OF ANY KIND, either express or implied.
****************************************************************************/

#ifndef HBENUMERATOR_H
#define HBENUMERATOR_H

/*! \file HbEnumerator.h */

// Qt
#include <QtCore/QMetaEnum>
// Hb
#include <core/HbNullable.h>

namespace hbprivate
{
    /*!
     * Internal class, TODOC.
     */
    template< typename Class >
    class HbEnumerator
    {
        Q_STATIC_CLASS( HbEnumerator )

    public:

        template< typename Enum >
        static QString name()
        {
            const QMetaObject & metaObject = Class::staticMetaObject;
            QMetaEnum metaEnum = metaObject.enumerator( indexOfEnumerator< Enum >() );

            return QString::fromLatin1( ( isEnumerator< Enum >( metaEnum ) ) ? metaEnum.name() : nullptr );
        }

        template< typename Enum >
        static qint16 count()
        {
            const QMetaObject & metaObject = Class::staticMetaObject;
            QMetaEnum metaEnum = metaObject.enumerator( indexOfEnumerator< Enum >() );

            return ( isEnumerator< Enum >( metaEnum ) ) ? metaEnum.keyCount() : 0;
        }

        template< typename Enum >
        static bool isFlag()
        {
            const QMetaObject & metaObject = Class::staticMetaObject;
            QMetaEnum metaEnum = metaObject.enumerator( indexOfEnumerator< Enum >() );

            return ( isEnumerator< Enum >( metaEnum ) ) ? metaEnum.isFlag() : false;
        }

        template< typename Enum >
        static nullable< Enum > value( qint16 index )
        {
            const QMetaObject & metaObject = Class::staticMetaObject;
            QMetaEnum metaEnum = metaObject.enumerator( indexOfEnumerator< Enum >() );

            qint32 value = ( isEnumerator< Enum >( metaEnum ) ) ? metaEnum.value( index ) : -1;
            return ( value >= 0 ) ? nullable< Enum >( ( Enum ) value ) : nullable< Enum >();
        }

        template< typename Enum >
        static qint16 index( Enum value )
        {
            const QMetaObject & metaObject = Class::staticMetaObject;
            QMetaEnum metaEnum = metaObject.enumerator( indexOfEnumerator< Enum >() );

            if( isEnumerator< Enum >( metaEnum ) )
            {
                for( qint16 index = 0; index < metaEnum.keyCount(); ++index )
                    if( ( Enum ) metaEnum.value( index ) == value ) return index;
            }

            return -1;
        }

        template< typename Enum >
        static QString toString( Enum value )
        {
            const QMetaObject & metaObject = Class::staticMetaObject;
            QMetaEnum metaEnum = metaObject.enumerator( indexOfEnumerator< Enum >() );

            return QString::fromLatin1( ( isEnumerator< Enum >( metaEnum ) ) ? metaEnum.valueToKey( ( qint32 ) value ) : nullptr );
        }

        template< typename Enum >
        static QStringList toString()
        {
            QStringList keys;

            const QMetaObject & metaObject = Class::staticMetaObject;
            QMetaEnum metaEnum = metaObject.enumerator( indexOfEnumerator< Enum >() );

            if( isEnumerator< Enum >( metaEnum ) )
                for( qint16 index = 0; index < metaEnum.keyCount(); ++index )
                {
                    qint32 value = metaEnum.value( index );
                    if( value >= 0 ) keys.append( QString::fromLatin1( metaEnum.valueToKey( ( Enum ) value ) ) );
                }

            return keys;
        }

        template< typename Enum >
        static nullable< Enum > fromString( const QString & label )
        {
            const QMetaObject & metaObject = Class::staticMetaObject;
            QMetaEnum metaEnum = metaObject.enumerator( indexOfEnumerator< Enum >() );

            qint32 value = ( !label.isEmpty() && isEnumerator< Enum >( metaEnum ) ) ? metaEnum.keyToValue( label.toLatin1().constData() ) : -1;
            return ( value >= 0 ) ? nullable< Enum >( ( Enum ) value ) : nullable< Enum >();
        }

    private:

        template< typename Enum >
        static qint32 indexOfEnumerator()
        {
            QString name = qTypeName< Enum >();
            const QMetaObject & metaObject = Class::staticMetaObject;

            return ( !name.isEmpty() ) ? metaObject.indexOfEnumerator( name.toLatin1().constData() ) : -1;
        }

        template< typename Enum >
        static bool isEnumerator( const QMetaEnum & metaEnum )
        {
            if( metaEnum.isValid() )
                return true;

            else
            {
                qWarning( "QEnum<%s>() -> unable to recover meta-data for enumerator", HbLatin1( qScopeName< Enum >() ) );
                return false;
            }
        }
    };
}

#endif // HBENUMERATOR_H
