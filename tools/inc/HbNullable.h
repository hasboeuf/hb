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
        * \class HbNullable
        * \brief The %HbNullable class represents an object whose underlying type is a value type that can also be assigned null.
        *
        * A nullable type can represent the correct range of values for its underlying value type, plus an additional null value.\n
        * For example, a Nullable<qint32> can be assigned any value from -2147483648 to 2147483647, or can be assigned the null value.
        */
        template< typename T >
        class HbNullable final
        {
        public :

            static const HbNullable< T > Null;


        public :

            /*!
            * Constructs a nullable type assigned to null.\n
            * Nullable type value is assigned to default-constructed value.
            */
            inline HbNullable()
            {
                _value = T();
                _isNull = true;
            }

            /*!
            * Constructs a defined nullable type initialized with value \a value.
            */
            inline HbNullable( const T & value )
            {
                _value = value;
                _isNull = false;
            }

            /*!
            * Constructs a defined nullable type initialized with value stored in variant \a variant.\n
            * If \a variant is invalid or cannot be converted to the template type T, nullable type becomes null and its value is assigned to default-constructed value.
            * \see QVariant
            */
            inline HbNullable( const QVariant & variant )
            {
                _isNull = !( variant.isValid() && variant.canConvert< T >() );
                _value = ( !_isNull ) ? variant.value< T >() : T();
            }

            /*!
            * Constructs a copy of nullable type \a nullable.
            */
            inline HbNullable( const HbNullable< T > & nullable ) :
                HbNullable()
            {
                if( &nullable != this )
                {
                    _value = nullable.value();
                    _isNull = nullable.isNull();
                }
            }

            /*!
            * Destroys the nullable type.
            */
            virtual ~HbNullable() = default;


            /*!
            * Returns true if nullable type is null; otherwise returns false.
            */
            inline bool isNull() const
            {
                return _isNull;
            }

            /*!
            * Returns nullable type value, regardless of its validity.
            */
            inline const T & value() const
            {
                return _value;
            }

            /*!
            * Returns nullable type value if valid; otherwise returns \a defaultValue.
            */
            inline const T & value( const T & defaultValue ) const
            {
                return ( _isNull ) ? defaultValue : _value;
            }

            /*!
            * Invalidate nullable type, while maintaining its value.
            */
            inline void invalidate()
            {
                _isNull = true;
            }


            /*!
            * Assigns \a value to this nullable type.
            */
            inline HbNullable< T > & operator =( const T & value )
            {
                _value = value;
                _isNull = false;

                return *this;
            }

            /*!
            * Assigns \a variant value to this nullable type.\n
            * If \a variant is invalid or cannot be converted to the template type T, nullable type becomes null and its value is assigned to default-constructed value.
            * \see QVariant
            */
            inline HbNullable< T > & operator =( const QVariant & variant )
            {
                _isNull = !( variant.isValid() && variant.canConvert< T >() );
                _value = ( !_isNull ) ? variant.value< T >() : T();

                return *this;
            }

            /*!
            * Assigns the content of nullable type \a nullable to this nullable type.
            */
            template< typename U >
            inline HbNullable< T > & operator =( const HbNullable< U > & nullable )
            {
                if( &nullable != this )
                {
                    _value = nullable.value();
                    _isNull = nullable.isNull();
                }

                return *this;
            }

            /*!
            * Returns true if this nullable type is defined and its value is equal to \a value; otherwise returns false.
            */
            inline bool operator ==( const T & value ) const
            {
                return ( !_isNull && ( _value == value ) );
            }

            /*!
            * Returns true if this nullable type is defined and its value is equal to \a variant value; otherwise returns false.\n
            * If \a variant is invalid or cannot be converted to the template type T, returns false.
            * \see QVariant
            */
            inline bool operator ==( const QVariant & variant ) const
            {
                return ( value.isValid() && value.template canConvert< T >() ) ?
                    operator ==( variant.value< T >() ) : false;
            }

            /*!
            * Returns true if nullable type \a nullable is equal to this nullable type; otherwise returns false.\n
            * Two nullable type are considered equal if they are both null or both defined with the same value.
            */
            inline bool operator ==( const HbNullable< T > & nullable ) const
            {
                if( _isNull && nullable.isNull() )
                    return true;

                if( !_isNull && !nullable.isNull() )
                    return ( _value == nullable.value() );

                return false;
            }

            /*!
            * Returns true if this nullable type is null or its value is not equal to \a value; otherwise returns false.
            */
            inline bool operator !=( const T & value ) const
            {
                return !operator ==( value );
            }

            /*!
            * Returns true if this nullable type is null or its value is not equal to \a variant value; otherwise returns false.\n
            * If \a variant is invalid or cannot be converted to the template type T, returns true.
            * \see QVariant
            */
            inline bool operator !=( const QVariant & variant ) const
            {
                return !operator ==( variant );
            }

            /*!
            * Returns true if nullable type \a nullable is not equal to this nullable type; otherwise returns false.\n
            * Two nullable type are considered equal if they are both null or both defined with the same value.
            */
            inline bool operator !=( const HbNullable< T > & nullable ) const
            {
                return !operator ==( nullable );
            }


            /*!
            * Returns the nullable type value converted to the template type T, regardless of its validity.
            */
            inline operator T() const
            {
                return value();
            }


        private :

            T _value;
            bool _isNull;
        };
    }
}

using hb::tools::HbNullable;

/*!
* Default nullable type assigned to null.
*/
template< typename T >
const HbNullable< T > HbNullable< T >::Null;

template< typename T >
using nullable = HbNullable< T >;


namespace HbPrivate
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

/*! 
* \def qRegisterNullableType( Type )
* \hideinitializer
* Registers the type HbNullable< Type >, and returns the associated Qt meta-type ID.
*/
#define qRegisterNullableType( Type ) \
    HbPrivate::qRegisterNullableType< Type >( #Type )

/*! 
* \def HbNullableTypeId( Type )
* \hideinitializer
* Returns the Qt meta-type ID of type HbNullable< Type > if registered; otherwise returns 0.
*/
#define HbNullableTypeId( Type ) \
    HbPrivate::HbNullableTypeId< Type >( #Type )


#endif // HBNULLABLE_H
