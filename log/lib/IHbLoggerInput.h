/****************************************************************************
** Copyright (C) 2012-2015 Adrien Gavignet (hasboeuf)
** Contact: adrien.gavignet@gmail.com
**
** This file is part of the Hb module. Provided "AS IS", WITHOUT WARRANTIES
** OR CONDITIONS OF ANY KIND, either express or implied.
****************************************************************************/

#ifndef IHBLOGGERINPUT_H
#define IHBLOGGERINPUT_H

/*! \file IHbLoggerInput.h */

// Local
#include <HbLogger.h>

namespace hb
{
    namespace log
    {
        /*!
         * TODOC.
         */
        class IHbLoggerInput
        {
        public:

            enum InputType : qint16
            {
                INPUT_LOCAL_SOCKET  = 0,
                INPUT_TCP_SOCKET    = 1,
                INPUT_UDP_SOCKET    = 2
            };

        public:
            virtual InputType type() const = 0;

        protected:

            virtual ~IHbLoggerInput(){} //!< \todo defaulted linux-g++ issue
        };
    }
}

#endif // IHBLOGGERINPUT_H