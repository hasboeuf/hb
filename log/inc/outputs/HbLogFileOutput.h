#ifndef HBLOGFILEOUTPUT_H
#define HBLOGFILEOUTPUT_H

/*! \file HbLogFileOutput.h */

#include <HbLog.h>
#include <outputs/HbLogAbstractOutput.h>

#include <QFile>
#include <QTextStream>

namespace hb
{
	namespace log
	{

		/*! \namespace hb::log */


		/*! 
		* \class HbLogFileOutput
		* \brief The %HbLogFileOutput class defines a file output.
		*
		* %HbLogFileOutput inherits from HbLogAbstractOutput.\n
		*/
        class HB_LOG_DECL HbLogFileOutput final : public HbLogAbstractOutput
		{
			Q_DISABLE_COPY( HbLogFileOutput )


		public :

			static const QString & fieldSeparator();

		public :

            HbLogFileOutput() = delete;
			HbLogFileOutput(const QString & path, quint32 max_size = 0, HbLogger::Levels level = HbLogger::LEVEL_ALL);
            virtual ~HbLogFileOutput();

			bool isValid() const;

		private :

			void processMessage( const HbLogMessage & message );


		private :

			QFile mFile;
			quint32 mMaxSize;
			QTextStream mStream;
		};
	}
}

#endif
