// Qt
#include <QtCore/QCoreApplication>
#include <QtCore/QDir>
#include <QtCore/QThread>
// Hb
#include <HbLogContext.h>
#include <HbLogService.h>

using namespace hb::log;

QString HbLogContext::msApplicationName;

HbLogContext::HbLogContext()
{
    if( msApplicationName.isEmpty() )
    {
        msApplicationName = qApp->applicationName();

        Q_ASSERT( !msApplicationName.isEmpty() );
    }

    mOwner = msApplicationName;
    mThread = 0;
    mLine = 0;
}

HbLogContext::HbLogContext(const QMessageLogContext & context ) :
    HbLogContext()
{
    mFile = QString(context.file).section(QDir::separator(), -1);
    mLine = context.line;
    mFunction = context.function;
}

HbLogContext::HbLogContext( const HbLogContext & context ) :
    HbLogContext()
{
    if( &context != this )
    {
        mOwner    = context.mOwner;
        mThread   = context.mThread;
        mFile     = context.mFile;
        mLine     = context.mLine;
        mFunction = context.mFunction;
    }
}

HbLogContext & HbLogContext::operator =( const HbLogContext & context )
{
    if( &context != this )
    {
        mOwner    = context.mOwner;
        mThread   = context.mThread;
        mFile     = context.mFile;
        mLine     = context.mLine;
        mFunction = context.mFunction;
    }

    return *this;
}


const QString & HbLogContext::owner() const
{
    return mOwner;
}

qint32 HbLogContext::thread() const
{
    return mThread;
}

const QString & HbLogContext::file() const
{
    return mFile;
}

qint32 HbLogContext::line() const
{
    return mLine;
}

const QString & HbLogContext::function() const
{
    return mFunction;
}

void HbLogContext::setOwner   ( const QString & owner ) {
    mOwner = owner;
}

void HbLogContext::setThread  ( qint32 thread ) {
    mThread = thread;
}

void HbLogContext::setFile    ( const QString & file ) {
    mFile = file;
}

void HbLogContext::setLine    ( quint32 line ) {
    mLine = line;
}

void HbLogContext::setFunction( const QString & function ) {
    mFunction = function;
}

void HbLogContext::print(QtMsgType type, const QString & message) const
{
    HbLogger::Level level = HbLogger::LEVEL_NONE;
    switch( type ) {
    case QtDebugMsg:
        level = HbLogger::LEVEL_DEBUG;
        break;
    case QtWarningMsg:
        level = HbLogger::LEVEL_WARNING;
        break;
    case QtCriticalMsg:
        level = HbLogger::LEVEL_CRITICAL;
        break;
    case QtFatalMsg:
        level = HbLogger::LEVEL_FATAL;
        break;
    case QtInfoMsg:
        level = HbLogger::LEVEL_INFO;
        break;
    default:
        Q_UNREACHABLE();
    }
    HbLogService::print( level, *this, message );
}

namespace hb
{
    namespace log
    {
        QDataStream & operator <<( QDataStream & stream, const HbLogContext & context )
        {
            stream << context.mOwner << context.mFile << context.mLine << context.mFunction;
            return stream;
        }

        QDataStream & operator >>( QDataStream & stream, HbLogContext & context )
        {
            stream >> context.mOwner >> context.mFile >> context.mLine >> context.mFunction;
            return stream;
        }
    }
}
