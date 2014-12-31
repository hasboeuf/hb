/****************************************************************************
** Copyright (C) 2012-2015 Adrien Gavignet (hasboeuf)
** Contact: adrien.gavignet@gmail.com
**
** This file is part of the Hb module. Provided "AS IS", WITHOUT WARRANTIES
** OR CONDITIONS OF ANY KIND, either express or implied.
****************************************************************************/

#ifndef HBLOGGERSTREAM_H
#define HBLOGGERSTREAM_H

/*! \file HbLoggerStream.h */

// Qt
#include <QtCore/QObject>
#include <QtCore/QSet>
// Hb
#include <HbLog.h>


namespace hb
{	
	namespace log
	{

		/*! \namespace hb::log */

        class HbLogManager;


        /*! 
        * \class HbLoggerStream
        * \brief The %HbLoggerStream class defines all enums needed in the log lib.
        *
        * Useful enums for users within %HbLoggerStream are:\n
        *   \li OutputFormat : represents the format to use to print a log message.
        *   \li Level  : represents the log level of an output.
        *   \li State   : represents the return code of the log lib.
        * All others enums are used for internal purpose within the lib./n
		*/
		class HB_LOG_DECL HbLoggerStream : public QObject
		{
			Q_OBJECT
			Q_DISABLE_COPY(HbLoggerStream)

			Q_ENUMS(State)

		public :
			static const char * DEFAULT_LOCAL_SERVER_NAME;

            enum State : qint16
			{
				INOUT_ADD_SUCCESS             = 0,
				INOUT_ID_ALREADY_EXISTS       = 1,
				INOUT_WRONG_PARAMETERS        = 2,
				INOUT_ALREADY_EXISTS          = 3,
				INOUT_CONSOLE_ALREADY_EXISTS  = 4, // Specific to Output.
				INOUT_DEL_SUCCESS             = 5,
				INOUT_DEL_FAIL                = 6
			};

			quint32 unusedId() const;

        protected :

            HbLoggerStream() = delete;
            HbLoggerStream( HbLogManager * parent );
            virtual ~HbLoggerStream() = default;

			QSet<quint32> mUsedId;

		public slots:
			void onStreamStateChanged(quint32 id, HbLoggerStream::State state);

        signals :

            /*! 
			* Triggered when an input has changed.
            * Dedicated to nofify the final application.
            */
            void streamStateChanged( quint32 id, HbLoggerStream::State state );
		};
	}
}

Q_DECLARE_METATYPE( hb::log::HbLoggerStream::State )

#endif // HBLOGGERSTREAM_H
