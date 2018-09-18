/****************************************************************************
** Copyright (C) 2012-2015 Adrien Gavignet (hasboeuf)
** Contact: adrien.gavignet@gmail.com
**
** This file is part of the Hb module. Provided "AS IS", WITHOUT WARRANTIES
** OR CONDITIONS OF ANY KIND, either express or implied.
****************************************************************************/

#ifndef HBLOGSERVICE_H
#define HBLOGSERVICE_H

/*! \file HbLogService.h */

// Qt
#include <QtCore/QThreadStorage>
#include <QtCore/QDebug>
// Hb
#include <HbLog.h>
#include <HbLogContext.h>
#include <HbGlobal.h>
#include <HbLogger.h>

namespace hb
{
    namespace log
    {
        class HbLoggerInputs;
        class HbLoggerOutputs;
        class HbLogManager;
        class HbLogGuiNotifier;

        /*!
         * HbLogService is the front-end interface of HbLog.
         * HbLogService is a threaded-singleton, that means it can be used from anywhere without any worries.
         * Features:
         * - Set pattern of log messages.
         * - Add/Remove log in/outputs.
         */
        namespace HbLogService
        {
            void install( const QString & logPattern = QString() );

            void print( HbLogger::Level level, const HbLogContext & context, const QString & message );

            /*!
             * Process list of args for HbLog.
             * Add in/output according to args.
             *
             * Each argument must fit the following usage (otherwise it is ignored).
             * Usage:
             * -hblog-(output|input)-local:name
             * -hblog-(output|input)-tcp:port[:ip]
             * -hblog-(output|input)-udp:port[:ip]
             * -hblog-output-file:dir:file_max_size
             */
            void processArgs( QStringList args );

            /*!
             * Request to add a udp socket input.
             * \param port Server port to connect.
             */
            void addUdpSocketInput( quint16 port );

            /*!
             * Request to add a tcp server input.
             * \param port Listening port.
             */
            void addTcpSocketInput( quint16 port );

            /*!
             * Request to add a local server input.
             * \param name Server name (defaulted on DEFAULT_LOCAL_SERVER_NAME).
             */
            void addLocalSocketInput( const QString & name = QString() );

            /*!
             * Request to add a console output.
             * Only one console per application is allowed.
             */
            void addConsoleOutput();

            /*!
             * Request to add a gui output.
             * \param notifier Gui notifier to connect.
             */
            void addGuiOutput( HbLogGuiNotifier * notifier );

            /*!
             * Request to add a file output.
             * \param dir Directory to put log files (according to QDir path).
             * \param max_size Max size of log file in Mo (if 0, msMaxFileSize (=100 Mo) will be used).
             */
            void addFileOutput( const QString & dir, quint32 max_size = 0 );

            /*!
             * Request to add a udp socket output.
             * \param port Port to connect.
             */
            void addUdpSocketOutput( const QString & ip, quint16 port );

            /*!
             * Request to add a tcp socket output.
             * \param ip Ip of the log server.
             * \param port Server port to connect.
             */
            void addTcpSocketOutput( const QString & ip, quint16 port );

            /*!
             * Request to add a local socket output.
             * \param name Server name (defaulted on DEFAULT_LOCAL_SERVER_NAME).
             */
            void addLocalSocketOutput( const QString & name = QString() );
        }
    }
}

#endif // HBLOGSERVICE_H
