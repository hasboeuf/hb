// Hb
#include <HbLogger.h>
#include <HbLogService.h>

using namespace hb::log;

QReadWriteLock HbLogger::msLock;
HbLogger::Levels HbLogger::msLevel = LEVEL_ALL;
HbLogger::Formats HbLogger::msFormat = OUTPUT_ALL;

void HbLogger::setLevel( Levels level )
{
    QWriteLocker locker( &msLock );
    HbLogger::msLevel = level;
}

HbLogger::Levels HbLogger::level() const
{
    QReadLocker locker( &msLock );
    return HbLogger::msLevel;
}


void HbLogger::setFormat( Formats format )
{
    QWriteLocker locker( &msLock );
    HbLogger::msFormat = ( format );
}

HbLogger::Formats HbLogger::format() const
{
    QReadLocker locker( &msLock );
    return HbLogger::msFormat;
}

void HbLogger::flush()
{
    dequeuePendingMessages();
}

void HbLogger::print( Level level, const HbLogContext & context, const QString & message )
{
    enqueueMessage(level, format(), context, message);
}
