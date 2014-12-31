/****************************************************************************
** Copyright (C) 2012-2015 Adrien Gavignet (hasboeuf)
** Contact: adrien.gavignet@gmail.com
**
** This file is part of the Hb module. Provided "AS IS", WITHOUT WARRANTIES
** OR CONDITIONS OF ANY KIND, either express or implied.
****************************************************************************/

#ifndef HbLogAbstractOutput_H
#define HbLogAbstractOutput_H

#include <IHbLoggerOutput.h>

class QMutex;

namespace hb
{
	namespace log
	{

        class HbLogMessage;

		class HbLogAbstractOutput :
            public virtual IHbLoggerOutput
		{
            Q_DISABLE_COPY( HbLogAbstractOutput )


		public :

			virtual ~HbLogAbstractOutput();

            virtual OutputType type() const final;
            virtual bool isValid() const;

            virtual void setLevel( HbLogger::Levels level ) final;
            virtual HbLogger::Levels level() const final;

            virtual void processMessage( const HbLogMessage & message ) = 0;

        protected :

            HbLogAbstractOutput() = delete;
            HbLogAbstractOutput( OutputType type, HbLogger::Levels level );


		private :

            QMutex * mpMutex;

            OutputType mType;
			HbLogger::Levels mLevel;
		};
	}
}

#endif
