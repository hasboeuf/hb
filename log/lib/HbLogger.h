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
#include <HbGlobal.h>
#include <HbLog.h>
#include <core/HbEnum.h>

namespace hb {
namespace log {
class HbLogContext;
class HbLogServiceController;

/*!
 * TODOC
 */
class HB_LOG_DECL HbLogger {
    Q_GADGET
    Q_DISABLE_COPY(HbLogger)
    Q_FRIEND_CLASS(HbLogServiceController)

public:
    enum Level : qint8 {
        LEVEL_NONE = 0,          // No Levels enabled
        LEVEL_DEBUG = 1 << 0,    // qDebug
        LEVEL_INFO = 1 << 1,     // qInfo
        LEVEL_WARNING = 1 << 2,  // qWarning
        LEVEL_CRITICAL = 1 << 3, // qCritical
        LEVEL_FATAL = 1 << 4,    // qFatal
        LEVEL_ALL = LEVEL_DEBUG | LEVEL_INFO | LEVEL_WARNING | LEVEL_CRITICAL | LEVEL_FATAL
    };

    Q_ENUM(Level)
    HB_ENUM(Level)
    Q_DECLARE_FLAGS(Levels, Level)

public:
    /*!
     * Set the general level of the log service (affected to the current thread).
     * All logger messages having a level which is not included in general level are ignored by HbLog.
     */
    virtual void setLevel(Levels level) final;

    /*!
     * Return the current general max level.
     * \return General max level.
     */
    virtual Levels level() const final;

    /*!
     * Dequeue pending log message.
     * Internal use.
     */
    virtual void flush() final;

protected:
    HbLogger() = default;
    virtual ~HbLogger() {
    } //!< \todo defaulted linux-g++ issue

    virtual void enqueueMessage(Level level, const HbLogContext& context, const QString& message) = 0;
    virtual void dequeuePendingMessages() = 0;

private:
    void print(Level level, const HbLogContext& context, const QString& message);

private:
    static QReadWriteLock msLock;
    static Levels msLevel;
};

Q_DECLARE_OPERATORS_FOR_FLAGS(HbLogger::Levels)
} // namespace log
} // namespace hb

using hb::log::HbLogger;

#endif // HBLOGGER_H
