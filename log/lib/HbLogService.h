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

namespace hb
{
    namespace log
    {
        class HbLoggerInputs;
        class HbLoggerOutputs;
        class HbLogManager;

        /*!
         * HbLogService is the front-end class of HbLog.
         * HbLogService is a threaded-singleton, that means it can be used from anywhere without any worries.
         * Features:
         * - Define convenient macros to push log message.
         * - Add/Remove log in/outputs.
         */
        class HB_LOG_DECL HbLogService
        {

        public:
            static void install( const QString & logPattern = QString() );
            static HbLogger * logger();
            static HbLoggerInputs * inputs();
            static HbLoggerOutputs * outputs();

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
            static void processArgs( QStringList args );

        private:
            HbLogService() = default;
            virtual ~HbLogService() = default;

            static void subscribe();

        private:
            static QThreadStorage< HbLogManager * > msManager;
        };
    }
}

#endif // HBLOGSERVICE_H
