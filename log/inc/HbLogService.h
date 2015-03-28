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

            static HbLogger * logger();
            static HbLoggerInputs * inputs();
            static HbLoggerOutputs * outputs();

            /*!
             * Process app args for HbLog.
             * See processArgs( QStringList args ) for usage.
             * \param argc Standard argc.
             * \param argv Standard argv.
             * \sa processArgs( QStringList args )
             */
            static void processArgs( int argc, char *argv[] );

            /*
             * Process list of args for HbLog.
             * Add in/output according to args.
             *
             * Each argument must fit the following usage (otherwise it is ignored).
             * Usage:
             * -hblog-(output|input)-local:name
             * -hblog-(output|input)-tcp:port[:ip]
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

/*!
 * Convenient macro to tag the beginning of a function.
 */
#define HbLogBegin() HbLogContext( __FILE__, __LINE__, Q_FUNC_INFO ) \
    .print(HbLogger::LEVEL_TRACE, "BEGIN")

/*!
 * Convenient macro to tag the end of a function.
 */
#define HbLogEnd() HbLogContext( __FILE__, __LINE__, Q_FUNC_INFO ) \
    .print(HbLogger::LEVEL_TRACE, "END")

/*!
* Should be used to write a new log message of type DEBUG.
*/
#define HbTrace( message, ... ) HbLogContext( __FILE__, __LINE__, Q_FUNC_INFO ) \
    .print(HbLogger::LEVEL_TRACE, message, ## __VA_ARGS__)

/*!
* Should be used to write a new log message of type DEBUG.
*/
#define HbDebug( message, ... ) HbLogContext( __FILE__, __LINE__, Q_FUNC_INFO ) \
    .print(HbLogger::LEVEL_DEBUG, message, ## __VA_ARGS__)

/*!
* Should be used to write a new log message of type INFO.
*/
#define HbInfo( message, ... ) HbLogContext( __FILE__, __LINE__, Q_FUNC_INFO ) \
    .print(HbLogger::LEVEL_INFO, message, ## __VA_ARGS__)


/*!
* Should be used to write a new log message of type WARNING.
*/
#define HbWarning( message, ... ) HbLogContext( __FILE__, __LINE__, Q_FUNC_INFO ) \
    .print(HbLogger::LEVEL_WARNING, message, ## __VA_ARGS__)

/*!
* Should be used to write a new log message of type ERROR.
*/
#define HbError( message, ... ) HbLogContext( __FILE__, __LINE__, Q_FUNC_INFO ) \
    .print(HbLogger::LEVEL_ERROR, message, ## __VA_ARGS__)

/*!
* Should be used to write a new log message of type CRITICAL.
*/
#define HbCritical( message, ... ) HbLogContext( __FILE__, __LINE__, Q_FUNC_INFO ) \
    .print(HbLogger::LEVEL_CRITICAL, message, ## __VA_ARGS__)

/*!
* Should be used to write a new log message of type FATAL.
*/
#define HbFatal( message, ... ) { HbLogContext( __FILE__, __LINE__, Q_FUNC_INFO ) \
    .print( HbLogger::LEVEL_FATAL, message, ## __VA_ARGS__ ); qAbort(); }


#endif // HBLOGSERVICE_H
