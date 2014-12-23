#ifndef IHBLOGGEROUTPUT_H
#define IHBLOGGEROUTPUT_H

// Hb
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
                OUTPUTmFile          = 2,
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
