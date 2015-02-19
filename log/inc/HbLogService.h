/****************************************************************************
** Copyright (C) 2012-2015 Adrien Gavignet (hasboeuf)
** Contact: adrien.gavignet@gmail.com
**
** This file is part of the Hb module. Provided "AS IS", WITHOUT WARRANTIES
** OR CONDITIONS OF ANY KIND, either express or implied.
****************************************************************************/

#ifndef HBLOGSERVICE_H
#define HBLOGSERVICE_H

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


        class HB_LOG_DECL HbLogService
        {
        public :

            static HbLogger * logger();
            static HbLoggerInputs * inputs();
            static HbLoggerOutputs * outputs();

            static void processArgs( int argc, char *argv[] );
            static void processArgs( QStringList args );
            // usage
            // -hblog-(output|input)-local:name
            // -hblog-(output|input)-tcp:port[:ip]
            // -hblog-output-file:dir:file_max_size

        private :

            HbLogService() = default;
            virtual ~HbLogService() = default;

            static void subscribe();


        private : 

            static QThreadStorage< HbLogManager * > msManager;
        };
    }
}

#define HbLogBegin() HbLogContext( __FILE__, __LINE__, Q_FUNC_INFO ) \
    .print(HbLogger::LEVEL_TRACE, "BEGIN")

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
