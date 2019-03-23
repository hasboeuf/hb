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
class HbLogManager : public QObject, public HbLogger {
    Q_DISABLE_COPY(HbLogManager)

public:
    HbLogManager(HbLoggerPool* pool, QObject* parent = nullptr);
    virtual ~HbLogManager();

private:
    void tryEnqueueMessage();
    void enqueueMessage(Level level, const HbLogContext& context, const QString& text);
    void dequeuePendingMessages();

    QPointer<HbLoggerPool> mPool;

    QList<HbLogMessage*> mMessages;
};
} // namespace log
} // namespace hb

#endif // HBLOGMANAGER_H
