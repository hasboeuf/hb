#ifndef HBDICTIONARYHELPER
#define HBDICTIONARYHELPER

//! \file HbDictionaryHelper.h

// Qt
#include <QtCore/QMap>
#include <QtCore/QString>
#include <QtNetwork/QTcpServer>
// Local
#include <HbTools.h>

namespace hb
{
    namespace tools
    {
        class HB_TOOLS_DECL HbDictionaryHelper
        {
        public:
            template< class K, class V >
            static const QList< QPair< K, V > > toPairList( const QHash< K, V > & input )
            {
                QList< QPair < K, V > > output;

                auto it = input.constBegin();
                while( it != input.constEnd() )
                {
                    output.append( qMakePair( it.key(), it.value() ) );
                    ++it;
                }
                return output;
            }

            template< class K, class V >
            static const QHash< K, V > toHash( const QList< QPair< K, V > > & input )
            {
                QHash< K, V > output;
                for( int i = 0; i < input.size(); ++i )
                {
                    output.insert( input.at( i ).first, input.at( i ).second );
                }
                return output;
            }

        };
    }
}

using hb::tools::HbDictionaryHelper;

#endif // HBDICTIONARYHELPER
