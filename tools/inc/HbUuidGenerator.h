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
#include <HbSingleton.h>
#include <HbGlobal.h>

namespace hb
{
    namespace tools
    {
        template< typename T >
        class HB_TOOLS_DECL HbUuidGenerator : public HbSingleton< HbUuidGenerator< T > >
        {
            Q_DISABLE_COPY( HbUuidGenerator )

            friend HbUuidGenerator * HbSingleton< HbUuidGenerator >::get();
            friend void HbSingleton< HbUuidGenerator >::kill();

        private:
            QMutex mMutex;
            T mCurrent;
            QQueue< T > mUnused;

        public:
            T getUuid()
            {
                //QMutexLocker( &mMutex );
                if( !mUnused.isEmpty() )
                {
                    return mUnused.dequeue();
                }
                else
                {
                    return mCurrent++;
                }
            }

            T getRandomUuid()
            {
                //QMutexLocker( &mMutex );

                T lowest = std::numeric_limits< T >::min();
                T highest = std::numeric_limits< T >::max();
                return qrand() % ((highest + 1) - lowest) + lowest;
            }

            void releaseUuid(T released_id)
            {
                //QMutexLocker( &mMutex );
                mUnused.enqueue( released_id );
            }

        private:
            HbUuidGenerator()
            {
                mCurrent = std::numeric_limits< T >::min();
            }

            ~HbUuidGenerator() = default;
        };
    }
}

#endif // HBUUIDGENERATOR_H
