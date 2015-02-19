/****************************************************************************
** Copyright (C) 2012-2015 Adrien Gavignet (hasboeuf)
** Contact: adrien.gavignet@gmail.com
**
** This file is part of the Hb module. Provided "AS IS", WITHOUT WARRANTIES
** OR CONDITIONS OF ANY KIND, either express or implied.
****************************************************************************/

#ifndef IHBLOGGEROUTPUT_H
#define IHBLOGGEROUTPUT_H

// Local
#include <HbLogger.h>

namespace hb
{    
    namespace log
    {
        class IHbLoggerOutput
        {
        public :

            enum OutputType : qint16
            {
                OUTPUT_CONSOLE       = 0,
                OUTPUT_GUI           = 1,
                OUTPUT_FILE          = 2,
                OUTPUT_LOCAL_SOCKET  = 3,
                OUTPUT_TCP_SOCKET    = 4
            };

        public :

            virtual OutputType type() const = 0;

            virtual void setLevel( HbLogger::Levels level ) = 0;
            virtual HbLogger::Levels level() const = 0;

        protected :

            virtual ~IHbLoggerOutput() = default;
        };
    }
}

#endif // IHBLOGGEROUTPUT_H
