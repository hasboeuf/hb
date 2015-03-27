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

class QTimerEvent;

namespace hb
{
    namespace log
    {
        class HbLoggerInputs;
        class HbLoggerOutputs;
        class HbLoggerPool;
        class HbLogMessage;
        class HbLogStdStream;


        /*!
        * Internal class, TODOC.
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

        protected:
            void timerEvent( QTimerEvent * event );

        private :
            void tryEnqueueMessage();
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
            qint32 mRetry;
        };
    }
}

#endif // HBLOGMANAGER_H
