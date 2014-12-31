/****************************************************************************
** Copyright (C) 2012-2015 Adrien Gavignet (hasboeuf)
** Contact: adrien.gavignet@gmail.com
**
** This file is part of the Hb module. Provided "AS IS", WITHOUT WARRANTIES
** OR CONDITIONS OF ANY KIND, either express or implied.
****************************************************************************/

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
