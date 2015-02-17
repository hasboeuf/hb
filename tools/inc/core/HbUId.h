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
            }

            ~HbUid()
            {
                HbUidGenerator< T, C >::get()->releaseUid( mUid );
            }

            virtual I uid() const final
            {
                return mUid;
            }

        protected:
            I mUid;
        };
    }
}

using hb::tools::HbUid;

#endif // HBUID_H
