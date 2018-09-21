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
#include <QtCore/QPointer>
// Hb
#include <HbLogger.h>
#include <HbLoggerPool.h>

class QTimerEvent;

namespace hb {
namespace log {
class HbLoggerInputs;
class HbLoggerOutputs;
class HbLoggerPool;
class HbLogMessage;

/*!
 * Internal class, TODOC.
 */
class HbLogManager final : public QObject, public HbLogger {
    Q_DISABLE_COPY(HbLogManager)

public:
    HbLogManager(HbLoggerPool* pool);
    virtual ~HbLogManager();

protected:
    void timerEvent(QTimerEvent* event);

private:
    void tryEnqueueMessage();
    void enqueueMessage(Level level, const HbLogContext& context, const QString& text);
    void dequeuePendingMessages();

private:
    QPointer<HbLoggerPool> mPool;

    QList<HbLogMessage*> mMessages;
    qint32 mRetry;
};
} // namespace log
} // namespace hb

#endif // HBLOGMANAGER_H
