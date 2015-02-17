/****************************************************************************
** Copyright (C) 2012-2015 Adrien Gavignet (hasboeuf)
** Contact: adrien.gavignet@gmail.com
**
** This file is part of the Hb module. Provided "AS IS", WITHOUT WARRANTIES
** OR CONDITIONS OF ANY KIND, either express or implied.
****************************************************************************/

#ifndef HBUID_H
#define HBUID_H

// Local
#include <HbTools.h>
#include <HbGlobal.h>
#include <core/HbUidGenerator.h>

namespace hb
{
    namespace tools
    {
        template< typename T = qint32, size_t C = CLASS_DEFAULT, bool Z = false >
        class HbUid
        {
            using I = typename std::conditional< std::is_integral< T >::value, T, qint32 >::type;

        public:
            HbUid()
            {
                mUid = HbUidGenerator< T, C >::get()->uid( Z );
                mReleaseUid = true;
            }

            ~HbUid()
            {
                if( mReleaseUid )
                {
                    HbUidGenerator< T, C >::get()->releaseUid( mUid );
                }
            }

            virtual I uid() const final
            {
                return mUid;
            }

            // Take the uid of another HbUid object.
            // Use with cautious, it breaks the unicity.
            virtual bool takeUid( HbUid * uid_object )
            {
                if( !uid_object )
                {
                    return false;
                }

                HbUidGenerator< T, C >::get()->releaseUid( mUid );
                mUid = uid_object->uid();
                uid_object->mReleaseUid = false;

                return true;
            }

        protected:
            I    mUid;
            bool mReleaseUid;
        };
    }
}

using hb::tools::HbUid;

#endif // HBUID_H
