/****************************************************************************
** Copyright (C) 2012-2015 Adrien Gavignet (hasboeuf)
** Contact: adrien.gavignet@gmail.com
**
** This file is part of the Hb module. Provided "AS IS", WITHOUT WARRANTIES
** OR CONDITIONS OF ANY KIND, either express or implied.
****************************************************************************/

#ifndef HBUID_H
#define HBUID_H

/*! \file HbUid.h */

// Local
#include <HbTools.h>
#include <HbGlobal.h>
#include <core/HbUidGenerator.h>

namespace hb
{
    namespace tools
    {
        /*!
         * HbUid provides a unique integer identifier.
         * \param C Uid belongings.
         * \sa HbUidGenerator
         */
        template< size_t C = CLASS_DEFAULT >
        class HbUid
        {

        public:
            HbUid()
            {
                mUid = HbUidGenerator< C >::get()->uid();
                mReleaseUid = true;
            }

            virtual ~HbUid()
            {
                if( mReleaseUid )
                {
                    HbUidGenerator< C >::get()->releaseUid( mUid );
                }
            }

            virtual quint32 uid() const final
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

                HbUidGenerator< C >::get()->releaseUid( mUid );
                mUid = uid_object->uid();
                uid_object->mReleaseUid = false;

                return true;
            }

        protected:
            quint32 mUid;
            bool mReleaseUid;
        };
    }
}

using hb::tools::HbUid;

#endif // HBUID_H
