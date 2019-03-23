// Qt
#include <QtCore/QCoreApplication>
#include <QtCore/QThread>
#include <QtCore/QTimer>
// Hb
#include <HbLogManager.h>
#include <HbLogMessage.h>
#include <HbLoggerPool.h>
#include <core/HbSteadyDateTime.h>

using namespace hb::log;
using namespace hb::tools;

HbLogManager::HbLogManager(HbLoggerPool* pool, QObject* parent) : QObject(parent), HbLogger() {
    mPool = pool;
}

HbLogManager::~HbLogManager() {
    dequeuePendingMessages();
}

void HbLogManager::tryEnqueueMessage() {
    if (!mPool->enqueueMessage(mMessages)) {
        QTimer::singleShot(0, this, &HbLogManager::tryEnqueueMessage);
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
