/****************************************************************************
** Copyright (C) 2012-2015 Adrien Gavignet (hasboeuf)
** Contact: adrien.gavignet@gmail.com
**
** This file is part of the Hb module. Provided "AS IS", WITHOUT WARRANTIES
** OR CONDITIONS OF ANY KIND, either express or implied.
****************************************************************************/

#ifndef HBLOGGERPOOL_H
#define HBLOGGERPOOL_H

/*! \file HbLoggerPool.h */

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

        /*!
         * TODOC.
         */
        class HbLoggerPool final : public QObject
        {
            Q_OBJECT
            Q_DISABLE_COPY( HbLoggerPool )

        private :

            static const quint16 MAX_CAPACITY = 500;
            static const quint16 TCP_PORT_MIN = 1024;
            // static const quint16 TCP_PORT_MAX = 65535; Useless as quint16 protects the max value.


        public :

            HbLoggerPool() = delete;
            HbLoggerPool( QThread * thread );
            virtual ~HbLoggerPool();

            loguid addTcpSocketInput  ( quint16 port, QString * error );
            loguid addLocalSocketInput( const QString & name, QString * error );
            bool   removeInput        ( loguid uid, QString * error );

            loguid addConsoleOutput    ( QString * error );
            loguid addGuiOutput        ( HbLogGuiNotifier * notifier, QString * error );
            loguid addFileOutput       ( const QString & path, quint32 max_size, QString * error );
            loguid addTcpSocketOutput  ( const QString & ip, quint16 port, QString * error );
            loguid addLocalSocketOutput( const QString & name, QString * error );
            bool   removeOutput        ( loguid uid, QString * error );

            IHbLoggerInput  * input ( loguid uid );
            IHbLoggerOutput * output( loguid uid );

            bool enqueueMessage( QList< HbLogMessage * > & buffer );

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
