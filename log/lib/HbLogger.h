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
            Q_FRIEND_CLASS ( HbLogContext )

        public:

            enum Level : qint16
            {
                LEVEL_NONE      = 0,        // No Levels enabled
                LEVEL_DEBUG     = 1 << 0,   // qDebug
                LEVEL_INFO      = 1 << 1,   // qInfo
                LEVEL_WARNING   = 1 << 2,   // qWarning
                LEVEL_CRITICAL  = 1 << 3,   // qCritical
                LEVEL_FATAL     = 1 << 4,   // qFatal
                LEVEL_ALL       = LEVEL_DEBUG | LEVEL_INFO | LEVEL_WARNING | LEVEL_CRITICAL | LEVEL_FATAL
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

            Q_ENUM( Level )
            Q_ENUM( Format )
            HB_ENUM( Level )
            HB_ENUM( Format )
            Q_DECLARE_FLAGS( Formats, Format )
            Q_DECLARE_FLAGS( Levels, Level )


        public:

            /*!
             * Set the general level of the log service (affected to the current thread).
             * All logger messages having a level which is not included in general level are ignored by HbLog.
             */
            virtual void setLevel( Levels level ) final;

            /*!
             * Return the current general max level.
             * \return General max level.
             */
            virtual Levels level() const final;

            /*!
            * Set the general output format.
            * \param format Output format.
            */
            virtual void setFormat( Formats format ) final;

            /*!
             * Return the current output format.
             * \return Output format.
             */
            virtual Formats format() const final;

            /*!
             * Dequeue pending log message.
             * Internal use.
             */
            virtual void flush() final;

        protected:

            HbLogger() = default;
            virtual ~HbLogger(){} //!< \todo defaulted linux-g++ issue

            virtual void enqueueMessage( Level level, Formats format, const HbLogContext & context, const QString & message ) = 0;
            virtual void dequeuePendingMessages() = 0;

        private:

            void print( Level level, const HbLogContext & context, const QString & message );

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
