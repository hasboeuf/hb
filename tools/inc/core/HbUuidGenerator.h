/****************************************************************************
** Copyright (C) 2012-2015 Adrien Gavignet (hasboeuf)
** Contact: adrien.gavignet@gmail.com
**
** This file is part of the Hb module. Provided "AS IS", WITHOUT WARRANTIES
** OR CONDITIONS OF ANY KIND, either express or implied.
****************************************************************************/

#ifndef HBUUIDGENERATOR_H
#define HBUUIDGENERATOR_H

// System
#include <limits>
// Qt
#include <QtCore/QObject>
#include <QtCore/QQueue>
#include <QtCore/QMutex>
// Hb
#include <HbTools.h>
#include <core/HbSingleton.h>
#include <HbGlobal.h>

namespace hb
{
    namespace tools
    {
        template< typename T = qint32, size_t C = CLASS_DEFAULT >
        class HB_TOOLS_DECL HbUuidGenerator : public HbSingleton< HbUuidGenerator< T, C > >
        {
            using I = typename std::conditional< std::is_integral< T >::value, T, qint32 >::type;

            Q_DISABLE_COPY( HbUuidGenerator )

            friend HbUuidGenerator * HbSingleton< HbUuidGenerator >::get();
            friend void HbSingleton< HbUuidGenerator >::kill();

        private:
            QMutex mMutex;
            QHash< ulong, I > mCurrent;
            QHash< ulong, QQueue< I > > mUnused;

        public:
            I uuid( bool zero_excluded = false )
            {
                QMutexLocker( &( this->mMutex ) );

                I value = 0;
                if( !mUnused[C].isEmpty() )
                {
                    value = mUnused[C].dequeue();
                }
                else
                {
                    value = mCurrent[C]++;
                }

                if( zero_excluded && value == 0 )
                {
                    return uuid( true );
                }

                return value;
            }

            I randomId()
            {
                QMutexLocker( &( this->mMutex ) );

                I lowest = std::numeric_limits< I >::min();
                I highest = std::numeric_limits< I >::max();
                return qrand() % ((highest + 1) - lowest) + lowest;
            }

            void releaseUuid( I released_id )
            {
                QMutexLocker( &( this->mMutex ) );

                mUnused[C].enqueue( released_id );
            }

        private:
            HbUuidGenerator()
            {
                mCurrent[C] = std::numeric_limits< I >::min();
            }

            ~HbUuidGenerator() = default;
        };
    }
}

#endif // HBUUIDGENERATOR_H
