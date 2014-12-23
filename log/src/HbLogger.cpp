// Hb
#include <HbLogger.h>
#include <HbLogService.h>

using namespace hb::log;


void qtHbLogHandler( QtMsgType type, const QMessageLogContext & context, const QString & message )
{
    switch( type )
    {
        case QtDebugMsg :

        #if !defined( QT_NO_DEBUG_OUTPUT )
            HbLogContext( context.file, context.line, context.function ).
                print( HbLogger::LEVEL_DEBUG, message.toUtf8().constData() );
        #else
            Q_UNUSED( context );
            Q_UNUSED( message );
        #endif

            break;

        case QtWarningMsg :

        #if !defined( QT_NO_WARNING_OUTPUT )
            HbLogContext( context.file, context.line, context.function ).
                print( HbLogger::LEVEL_WARNING, message.toUtf8().constData() );
        #else
            Q_UNUSED( context );
            Q_UNUSED( message );
        #endif

            break;

        case QtCriticalMsg :

            HbLogService::logger()->
                print( HbLogger::LEVEL_ERROR, message.toUtf8().constData() );

            Q_UNUSED( context );
            break;

        case QtFatalMsg :

			fprintf(stderr, "%s\n", HbLatin1(message));
            break;

        default :

            Q_UNREACHABLE();
            break;
    }
}


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
    HbLogger::msFormat = ( format & ~HbLogger::OUTPUT_SYSTEM );
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


void HbLogger::qtMessageHandler( bool enabled )
{
    qInstallMessageHandler( ( enabled ) ? qtHbLogHandler : nullptr );
}

void HbLogger::print( Level level, const char * message, ... )
{
    if( message )
    {
        va_list args;
        va_start( args, message );

        print( level, message, args );
        va_end( args );
    }
}

void HbLogger::print( Level level, const char * message, va_list args )
{
    print( level, HbLogContext(), message, args );
}


void HbLogger::print( Level level, const HbLogContext & context, const char * message, va_list args )
{
    if( message )
    {
    #if defined( QT_NO_DEBUG ) 
        if( ( level == LEVEL_TRACE ) || ( level == LEVEL_DEBUG ) )
            return;
    #endif

        if( this->level() & level )
        {
            QString buffer = QString().vsprintf( message, args );

			if (!buffer.isEmpty())
			{
				
				enqueueMessage(level, format(), context, buffer);
			}
        }
    }
}

void HbLogger::system( Level level, const HbLogContext & context, const char * message, va_list args )
{
    if( message )
        if( this->level() & level )
        {
            QString buffer = QString().vsprintf( message, args );

            if( !buffer.isEmpty() )
                enqueueMessage( level, format() | HbLogger::OUTPUT_SYSTEM, context, buffer );
        }
}
