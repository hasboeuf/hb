/****************************************************************************
** Copyright (C) 2012-2015 Adrien Gavignet (hasboeuf)
** Contact: adrien.gavignet@gmail.com
**
** This file is part of the Hb module. Provided "AS IS", WITHOUT WARRANTIES
** OR CONDITIONS OF ANY KIND, either express or implied.
****************************************************************************/

#ifndef HBLOGABSTRACTINPUT_H
#define HBLOGABSTRACTINPUT_H

/*! \file HbLogAbstractInput.h */

// Hb
#include <core/HbUid.h>
// Local
#include <IHbLoggerInput.h>

namespace hb
{
    namespace log
    {
        /*!
         * TODOC.
         */
        class HbLogAbstractInput :
            public IHbLoggerInput,
            public HbUid< loguid, CLASS_LOG, true >
        {
            Q_DISABLE_COPY( HbLogAbstractInput )

        public:
            virtual ~HbLogAbstractInput(){} //!< \todo defaulted linux-g++ issue
            virtual InputType type() const final;

        protected:
            HbLogAbstractInput() = default;
            HbLogAbstractInput( InputType type );

        private:
            InputType mType;
        };
    }
}

#endif // HBLOGABSTRACTINPUT_H
