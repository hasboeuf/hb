/****************************************************************************
** Copyright (C) 2012-2015 Adrien Gavignet (hasboeuf)
** Contact: adrien.gavignet@gmail.com
**
** This file is part of the Hb module. Provided "AS IS", WITHOUT WARRANTIES
** OR CONDITIONS OF ANY KIND, either express or implied.
****************************************************************************/

#ifndef HBLOGMANAGER_H
#define HBLOGMANAGER_H

/*! \file HbLogManager.h */

// Qt
#include <QtCore/QMutex>
// Hb
#include <HbLogger.h>

namespace hb
{	
	namespace log
	{

		/*! \namespace hb::log */

        class HbLoggerInputs;
        class HbLoggerOutputs;
        class HbLoggerPool;
        class HbLogMessage;
        class HbLogStdStream;


        /*! 
        * \class HbLogManager
        * \brief The %HbLogManager class defines the front-end of the logger.
        *
        * %HbLogManager is a threaded-singleton, that means it can be used from anywhere without any worries.\n
		* %HbLogManager provides convenient macros to push new logger message.\n
		* Also, user can add different outputs and inputs.\n
        */
        class HbLogManager final : public QObject, public HbLogger
		{
            Q_DISABLE_COPY( HbLogManager )


		public :

            HbLogManager();
			virtual ~HbLogManager();

            HbLoggerInputs * inputs() const;
            HbLoggerOutputs * outputs() const;
            HbLoggerPool * pool() const;

		private :

			void enqueueMessage( Level level, Formats format, const HbLogContext & context, const QString & text );
			void dequeuePendingMessages();

        private :

            static QMutex msMutex;
            static quint8 msInstances;

            static QThread * msThreadPool;
            static HbLoggerPool * msLoggerPool;

            HbLoggerInputs * mpInputs;
            HbLoggerOutputs * mpOutputs;
            QList< HbLogMessage * > mMessages;
		};
	}
}

#endif // HBLOGMANAGER_H
