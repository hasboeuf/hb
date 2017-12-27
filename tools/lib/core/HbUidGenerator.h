/****************************************************************************
** Copyright (C) 2012-2015 Adrien Gavignet (hasboeuf)
** Contact: adrien.gavignet@gmail.com
**
** This file is part of the Hb module. Provided "AS IS", WITHOUT WARRANTIES
** OR CONDITIONS OF ANY KIND, either express or implied.
****************************************************************************/

#ifndef HBUIDGENERATOR_H
#define HBUIDGENERATOR_H

/*! \file HbUidGenerator.h */

// System
#include <limits>
// Qt
#include <QtCore/QObject>
#include <QtCore/QQueue>
#include <QtCore/QMutex>
#include <QtCore/QHash>
// Hb
#include <HbTools.h>
#include <core/HbSingleton.h>
#include <HbGlobal.h>

namespace hb
{
    namespace tools
    {
        /*!
         * HbUidGenerator maintains a list of unique integer identifiers for the application.
         * It is a singleton class.
         * \param T Type of integer.
         * \param C Uid belongings.
         * \sa HbUid
         */
        template< typename T = qint32, size_t C = CLASS_DEFAULT >
        class HbUidGenerator : public HbSingleton< HbUidGenerator< T, C > >
        {
            using I = typename std::conditional< std::is_integral< T >::value, T, qint32 >::type;

            Q_DISABLE_COPY( HbUidGenerator )

            // https://connect.microsoft.com/VisualStudio/feedbackdetail/view/731937/friend-template-bug-in-msvc
            //friend HbUidGenerator< T, C > * HbSingleton< HbUidGenerator< T, C > >::get();
            //friend void HbSingleton< HbUidGenerator< T, C > >::kill();
            friend class HbSingleton< HbUidGenerator< T, C > >;

        private:
            QMutex mMutex;
            QHash< ulong, I > mCurrent;
            QHash< ulong, QQueue< I > > mUnused;

        public:
            I uid( bool zero_excluded = false )
            {
                I value = 0;

                { // Mutex area
                    QMutexLocker locker( &mMutex );

                    if( !mUnused[C].isEmpty() )
                    {
                        value = mUnused[C].dequeue();
                    }
                    else
                    {
                        value = mCurrent[C]++;
                    }
                }

                if( zero_excluded && value == 0 )
                {
                    return uid( true );
                }

                return value;
            }

            I randomId()
            {
                QMutexLocker locker( &mMutex );

                I lowest = std::numeric_limits< I >::min();
                I highest = std::numeric_limits< I >::max();
                return qrand() % ((highest + 1) - lowest) + lowest;
            }

            void releaseUid( I released_id )
            {
                QMutexLocker locker( &mMutex );

                mUnused[C].enqueue( released_id );
            }

        private:
            HbUidGenerator()
            {
                mCurrent[C] = std::numeric_limits< I >::min();
            }

            ~HbUidGenerator() = default;
        };
    }
}

#endif // HBUIDGENERATOR_H
