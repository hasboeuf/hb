#ifndef HBLOGCONSOLEOUTPUT_H
#define HBLOGCONSOLEOUTPUT_H

/*! \file HbLogConsoleOutput.h */

#include <outputs/HbLogAbstractOutput.h>

namespace hb
{
	namespace log
	{

		/*! \namespace hb::log */


        /*! 
        * \class HbLogConsoleOutput
        * \brief The %HbLogConsoleOutput class defines a console output.
        *
        * %HbLogConsoleOutput inherits from HbLogAbstractOutput.\n
        */
        class HbLogConsoleOutput final : public HbLogAbstractOutput
		{
            Q_DISABLE_COPY( HbLogConsoleOutput )


		public :

            HbLogConsoleOutput( HbLogger::Levels level = HbLogger::LEVEL_ALL );
            virtual ~HbLogConsoleOutput() = default;

        private :

		    void processMessage( const HbLogMessage & message );
		};
	}
}

#endif
