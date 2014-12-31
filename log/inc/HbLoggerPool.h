/****************************************************************************
** Copyright (C) 2012-2015 Adrien Gavignet (hasboeuf)
** Contact: adrien.gavignet@gmail.com
**
** This file is part of the Hb module. Provided "AS IS", WITHOUT WARRANTIES
** OR CONDITIONS OF ANY KIND, either express or implied.
****************************************************************************/

#ifndef HBLOGGERPOOL_H
#define HBLOGGERPOOL_H

// Qt
#include <QtCore/QHash>
#include <QtCore/QReadWriteLock>
// Hb
#include <HbLoggerStream.h>
#include <HbGlobal.h>

class QTimer;

namespace hb
{	
	namespace log
	{

        class IHbLoggerInput;
        class IHbLoggerOutput;
        class HbLogAbstractInput;
        class HbLogAbstractOutput;
        class HbLogGuiNotifier;
        class HbLogMessage;


        class HbLoggerPool final : public QObject
		{
			Q_OBJECT
            Q_DISABLE_COPY( HbLoggerPool )

        private :

            static const quint16 MAX_CAPACITY = 500;
            static const quint16 TCP_PORT_MIN = 1024;
            static const quint16 TCP_PORT_MAX = 65535;


		public :

            HbLoggerPool() = delete;
            HbLoggerPool( QThread * thread );
            virtual ~HbLoggerPool();

            bool addTcpSocketInput  ( quint32 id, quint32 port );
            bool addLocalSocketInput( quint32 id, const QString & name = QString() );
            bool removeInput        ( quint32 id );

            bool addConsoleOutput    ( quint32 id );
            bool addGuiOutput        ( quint32 id, HbLogGuiNotifier * notifier );
            bool addFileOutput       ( quint32 id, const QString & path, quint32 max_size = 0 );
            bool addTcpSocketOutput  ( quint32 id, const QString & ip, quint32 port );
            bool addLocalSocketOutput( quint32 id, const QString & name = QString() );
            bool removeOutput        ( quint32 id );

            IHbLoggerInput  * input ( quint32 id );
            IHbLoggerOutput * output( quint32 id );

            bool enqueueMessage( QList< HbLogMessage * > & buffer );

        signals :

            // To HbLogService
            void streamStateChanged( quint32 id, HbLoggerStream::State state );

        private callbacks :

            // From QThread
            void running();
            void process();


		private :

			QAtomicInt mAtomic;
            QReadWriteLock mInputsLock;
            QReadWriteLock mOutputsLock;

            QTimer * mpClock;
            qint32 mCapacity;

            QList< HbLogMessage * > mLoggerStream;
            QList< HbLogMessage * > mInputsStream;

            QHash< quint32, HbLogAbstractInput * > mInputs;
			QHash< quint32, HbLogAbstractOutput * > mOutputs;
		};
	}
}

#endif // HBLOGGERPOOL_H
