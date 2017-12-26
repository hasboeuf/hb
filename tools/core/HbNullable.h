/****************************************************************************
** Copyright (C) 2012-2015 Adrien Gavignet (hasboeuf)
** Contact: adrien.gavignet@gmail.com
**
** This file is part of the Hb module. Provided "AS IS", WITHOUT WARRANTIES
** OR CONDITIONS OF ANY KIND, either express or implied.
****************************************************************************/

#ifndef HBNULLABLE_H
#define HBNULLABLE_H

/*! \file HbNullable.h */

// Qt
#include <QtCore/QVariant>
// Hb
#include <HbGlobal.h>
#include <HbTools.h>

namespace hb
{
    namespace tools
    {
        /*!
         * HbNullable provides a C++ version of C# Nullable.
         */
        template< typename T >
        class HbNullable final
        {
        public:

            static const HbNullable< T > Null;


        public:

            inline HbNullable()
            {
                mValue = T();
                mIsNull = true;
            }

            inline HbNullable( const T & value )
            {
                mValue = value;
                mIsNull = false;
            }

            inline HbNullable( const QVariant & variant )
            {
                mIsNull = !( variant.isValid() && variant.canConvert< T >() );
                mValue = ( !mIsNull ) ? variant.value< T >() : T();
            }

            inline HbNullable( const HbNullable< T > & nullable ) :
                HbNullable()
            {
                if( &nullable != this )
                {
                    mValue = nullable.value();
                    mIsNull = nullable.isNull();
                }
            }

            virtual ~HbNullable() = default;

            inline bool isNull() const
            {
                return mIsNull;
            }

            inline const T & value() const
            {
                return mValue;
            }

            inline const T & value( const T & defaultValue ) const
            {
                return ( mIsNull ) ? defaultValue : mValue;
            }

            inline void invalidate()
            {
                mIsNull = true;
            }

            inline HbNullable< T > & operator =( const T & value )
            {
                mValue = value;
                mIsNull = false;

                return *this;
            }

            inline HbNullable< T > & operator =( const QVariant & variant )
            {
                mIsNull = !( variant.isValid() && variant.canConvert< T >() );
                mValue = ( !mIsNull ) ? variant.value< T >() : T();

                return *this;
            }

            template< typename U >
            inline HbNullable< T > & operator =( const HbNullable< U > & nullable )
            {
                if( &nullable != this )
                {
                    mValue = nullable.value();
                    mIsNull = nullable.isNull();
                }

                return *this;
            }

            inline bool operator ==( const T & value ) const
            {
                return ( !mIsNull && ( mValue == value ) );
            }

            inline bool operator ==( const QVariant & variant ) const
            {
                return ( value.isValid() && value.template canConvert< T >() ) ?
                    operator ==( variant.value< T >() ) : false;
            }

            inline bool operator ==( const HbNullable< T > & nullable ) const
            {
                if( mIsNull && nullable.isNull() )
                    return true;

                if( !mIsNull && !nullable.isNull() )
                    return ( mValue == nullable.value() );

                return false;
            }

            inline bool operator !=( const T & value ) const
            {
                return !operator ==( value );
            }

            inline bool operator !=( const QVariant & variant ) const
            {
                return !operator ==( variant );
            }

            inline bool operator !=( const HbNullable< T > & nullable ) const
            {
                return !operator ==( nullable );
            }

            inline operator T() const
            {
                return value();
            }


        private:

            T mValue;
            bool mIsNull;
        };
    }
}

using hb::tools::HbNullable;

template< typename T >
const HbNullable< T > HbNullable< T >::Null;

template< typename T >
using nullable = HbNullable< T >;

namespace hbprivate
{
    template< typename Type >
    inline qint32 HbNullableTypeId( const char * typeName )
    {
        if( !typeName )
        {
            qWarning("HbNullableTypeId<%s>() -> null type name not supported", HbLatin1(qScopeName< Type >()));
            return 0;
        }

        QString nullableType = QStringLiteral( "HbNullable<%1>" ).arg( QString::fromLatin1( typeName ) );
        return QMetaType::type( nullableType.toLatin1().constData() );
    }

    template< typename Type >
    inline qint32 qRegisterNullableType( const QString & typeName )
    {
        QString nullableType = QStringLiteral( "HbNullable<%1>" ).arg( typeName );
        return qRegisterMetaType< HbNullable< Type > >( nullableType.toLatin1().constData() );
    }
}

#define qRegisterNullableType( Type ) \
    hbprivate::qRegisterNullableType< Type >( #Type )

#define HbNullableTypeId( Type ) \
    hbprivate::HbNullableTypeId< Type >( #Type )

#endif // HBNULLABLE_H
