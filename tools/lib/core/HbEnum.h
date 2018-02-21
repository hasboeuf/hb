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

// Qt
#include <QMetaEnum>
// Hb
#include <HbTools.h>
#include <HbGlobal.h>

namespace hb {
    namespace tools {

        template< typename Enum >
        class HbEnum
        {
            Q_STATIC_CLASS( HbEnum )

        public:
            static QStringList toString() {
                QStringList keys;
                const QMetaEnum metaEnum = HbEnum::metaEnum();
                for( qint16 index = 0; index < metaEnum.keyCount(); ++index ) {
                    qint32 value = metaEnum.value( index );
                    Q_ASSERT( value != -1 );
                    auto str = metaEnum.valueToKey( ( Enum ) value );
                    Q_ASSERT( str );
                    keys.append( QString::fromLatin1( str ) );
                }
                return keys;
            }

            static QString toString( Enum value ) {
                return HbEnum::toString( ( qint32 ) value );
            }

            static QString toString( qint32 value ) {
                const QMetaEnum metaEnum = HbEnum::metaEnum();
                auto str = metaEnum.valueToKey( ( qint32 ) value );
                Q_ASSERT( str );
                return QString::fromLatin1( str );
            }

            static Enum fromString( const QString & label )
            {
                const QMetaEnum metaEnum = HbEnum::metaEnum();

                qint32 key = metaEnum.keyToValue( label.toLatin1().constData() );
                Q_ASSERT( key != -1 );
                return ( Enum ) key;
            }

        private:
            static QMetaEnum metaEnum() {
                auto enumerator = QMetaEnum::fromType<Enum>();
                Q_ASSERT( enumerator.isValid() );
                return enumerator;
            }
        };
    }
}

/*! \def HB_ENUM
 * Macro that creates a Meta{MyEnum} static class
 * Provide convenient methods for introspection with the help of QMetaEnum.
 * \note Q_ENUM needs to be called first.
 */
#define HB_ENUM( Enum ) \
    typedef hb::tools::HbEnum< Enum > Meta ## Enum;
#endif
