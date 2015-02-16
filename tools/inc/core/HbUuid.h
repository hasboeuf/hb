/****************************************************************************
** Copyright (C) 2012-2015 Adrien Gavignet (hasboeuf)
** Contact: adrien.gavignet@gmail.com
**
** This file is part of the Hb module. Provided "AS IS", WITHOUT WARRANTIES
** OR CONDITIONS OF ANY KIND, either express or implied.
****************************************************************************/

#ifndef HBUUID_H
#define HBUUID_H

// Local
#include <HbTools.h>
#include <HbGlobal.h>
#include <core/HbUuidGenerator.h>

namespace hb
{
    namespace tools
    {
        template< typename T = qint32, size_t C = CLASS_DEFAULT, bool Z = false >
        class HB_TOOLS_DECL HbUuid
        {
            using I = typename std::conditional< std::is_integral< T >::value, T, qint32 >::type;

        public:
            HbUuid()
            {
                mUuid = HbUuidGenerator< T, C >::get()->uuid( Z );
            }

            ~HbUuid()
            {
                HbUuidGenerator< T, C >::get()->releaseUuid( mUuid );
            }

            I uuid() const
            {
                return mUuid;
            }

        private:
            I mUuid;
        };
    }
}

#endif // HBUUID_H
