// Qt
#include <QtCore/QCoreApplication>
#include <QtCore/QThread>
#include <QtCore/QTime>
// Hb
#include <HbLogManager.h>
#include <HbLogMessage.h>
#include <HbLoggerPool.h>
#include <core/HbSteadyDateTime.h>

using namespace hb::log;
using namespace hb::tools;

HbLogManager::HbLogManager(HbLoggerPool* pool) : QObject(), HbLogger() {
    mPool = pool;
    mRetry = 0;
}

HbLogManager::~HbLogManager() {
    if (mRetry)
        killTimer(mRetry);
    dequeuePendingMessages();
}

void HbLogManager::timerEvent(QTimerEvent* event) {
    Q_UNUSED(event)

    tryEnqueueMessage();
}

void HbLogManager::tryEnqueueMessage() {
    if (mPool->enqueueMessage(mMessages)) {
        if (mRetry) {
            // printf( "HbLogManager: push buffer ok.\n" );
            killTimer(mRetry);
            mRetry = 0;
        }
    } else {
        if (!mRetry) {
            // printf( "HbLogManager: locked pool, %d message(s) in buffer, retry in 200 ms.\n", mMessages.size() );
            mRetry = startTimer(200);
        }
    }
}

void HbLogManager::enqueueMessage(Level level, const HbLogContext& context, const QString& text) {
    qint64 timestamp = HbSteadyDateTime::now().toNsSinceEpoch();

    HbLogMessage* message = new HbLogMessage(level, context, timestamp, text);

    mMessages.push_back(message);
    tryEnqueueMessage();
}

void HbLogManager::dequeuePendingMessages() {
    if (!mMessages.isEmpty()) {
        while (!mPool->enqueueMessage(mMessages)) {
            QThread::yieldCurrentThread();
        }
    }
}
