/****************************************************************************
** Copyright (C) 2012-2015 Adrien Gavignet (hasboeuf)
** Contact: adrien.gavignet@gmail.com
**
** This file is part of the Hb module. Provided "AS IS", WITHOUT WARRANTIES
** OR CONDITIONS OF ANY KIND, either express or implied.
****************************************************************************/

#ifndef HBLOGGER_H
#define HBLOGGER_H

/*! \file HbLogger.h */

// Qt
#include <QtCore/QReadWriteLock>

// Hb
#include <HbLog.h>
#include <HbGlobal.h>
#include <core/HbEnum.h>

namespace hb
{
    namespace log
    {
        class HbLogContext;

        /*!
         * TODOC
         */
        class HB_LOG_DECL HbLogger
        {
            Q_GADGET
            Q_DISABLE_COPY ( HbLogger )
            Q_ENUMS_HANDLER( HbLogger )
            Q_FRIEND_CLASS ( HbLogContext )

            Q_ENUMS( Level )
            Q_ENUMS( Format )

        public:

            enum Level : qint16
            {
                LEVEL_NONE      = 0,        // No Levels enabled
                LEVEL_TRACE     = 1 << 0,   // Macro HbTrace    to be logged.
                LEVEL_DEBUG     = 1 << 1,   // Macro HbDebug    to be logged.
                LEVEL_INFO      = 1 << 2,   // Macro HbInfo     to be logged.
                LEVEL_WARNING   = 1 << 3,   // Macro HbWarning  to be logged.
                LEVEL_ERROR     = 1 << 4,   // Macro HbError    to be logged.
                LEVEL_CRITICAL  = 1 << 5,   // Macro HbCritical to be logged.
                LEVEL_FATAL     = 1 << 6,   // Macro HbFatal    to be logged.
                LEVEL_ALL       = LEVEL_TRACE | LEVEL_DEBUG | LEVEL_INFO | LEVEL_WARNING | LEVEL_ERROR | LEVEL_CRITICAL | LEVEL_FATAL
            };

            enum Format : qint16
            {
                OUTPUT_LEVEL   = 1 << 0,
                OUTPUT_TIME    = 1 << 1,
                OUTPUT_WHO     = 1 << 2,
                OUTPUT_WHERE   = 1 << 3,     // File + Function + Line.
                OUTPUT_TEXT    = 1 << 4,
                OUTPUT_ALL     = OUTPUT_LEVEL | OUTPUT_TIME | OUTPUT_WHO | OUTPUT_WHERE | OUTPUT_TEXT
            };

            Q_META_ENUMS( Format )
            Q_META_ENUMS( Level )

            Q_DECLARE_FLAGS( Formats, Format )
            Q_DECLARE_FLAGS( Levels, Level )


        public:

            /*!
             * Set the general level of the log service (affected to the current thread).
             * All logger messages having a level which is not included in general level are ignored by HbLog.
             */
            virtual void setLevel( Levels level ) final;

            /*!
             * Return the current general level of the current thread.
             */
            virtual Levels level() const final;

            virtual void setFormat( Formats format ) final;
            virtual Formats format() const final;

            virtual void flush() final;

            virtual void qtMessageHandler( bool enabled ) final;

            /*!
             * Push a log message into the log lib.
             * Note that it is kindly recommended to use macros of HbLogService to call this method.
             */
            virtual void print( Level level, const char * message, ... ) final;
            virtual void print( Level level, const char * message, va_list args ) final;

        protected:

            HbLogger() = default;
            virtual ~HbLogger(){} // = default; TODO linux-g++ issue

            virtual void enqueueMessage( Level level, Formats format, const HbLogContext & context, const QString & message ) = 0;
            virtual void dequeuePendingMessages() = 0;

        private:

            void print( Level level, const HbLogContext & context, const char * message, va_list args );

        private:

            static QReadWriteLock msLock;
            static Levels msLevel;
            static Formats msFormat;
        };

        Q_DECLARE_OPERATORS_FOR_FLAGS( HbLogger::Levels )
        Q_DECLARE_OPERATORS_FOR_FLAGS( HbLogger::Formats )
    }
}

using hb::log::HbLogger;

#endif // HBLOGGER_H
