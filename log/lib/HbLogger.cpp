// Hb
#include <HbLogService.h>
#include <HbLogger.h>

using namespace hb::log;

QReadWriteLock HbLogger::msLock;
HbLogger::Levels HbLogger::msLevel = LEVEL_ALL;

void HbLogger::setLevel(Levels level) {
    QWriteLocker locker(&msLock);
    HbLogger::msLevel = level;
}

HbLogger::Levels HbLogger::level() const {
    QReadLocker locker(&msLock);
    return HbLogger::msLevel;
}

void HbLogger::flush() {
    dequeuePendingMessages();
}

void HbLogger::print(Level level, const HbLogContext& context, const QString& message) {
    enqueueMessage(level, context, message);
}
