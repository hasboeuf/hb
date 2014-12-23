#ifndef IHBLOGGERINPUT_H
#define IHBLOGGERINPUT_H

// Qt
#include <QtCore/QtGlobal>

namespace hb
{
	namespace log
	{
        class IHbLoggerInput
		{
        public :

            enum InputType : qint16
            {
                INPUT_LOCAL_SOCKET  = 0,
                INPUT_TCP_SOCKET    = 1
            };


		public :

            virtual InputType type() const = 0;

        protected :

            virtual ~IHbLoggerInput() = default;
		};
	}
}

#endif // IHBLOGGERINPUT_H
