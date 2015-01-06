// Qt
#include <QtCore/QCoreApplication>
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
    mLine = -1;
}

HbLogContext::HbLogContext( const HbLogContext & context ) :
    HbLogContext()
{
    if( &context != this )
    {
        mOwner    = context.mOwner;
        mFile     = context.mFile;
        mLine     = context.mLine;
        mFunction = context.mFunction;
    }
}

HbLogContext::HbLogContext( const char * file, qint32 line, const char * function ) :
    HbLogContext()
{
    mFile     = QString::fromLatin1( file );
    mLine     = ( !mFile.isEmpty() ) ? line : -1;
    mFunction = QString::fromLatin1( function );
}

HbLogContext::HbLogContext( const QString & owner, const char * file, qint32 line, const char * function )
{
    q_assert( !( mOwner = owner ).isEmpty() );
    mFile     = QString::fromLatin1( file );
    mLine     = ( !mFile.isEmpty() ) ? line : -1;
    mFunction = QString::fromLatin1( function );
}


HbLogContext & HbLogContext::operator =( const HbLogContext & context )
{
    if( &context != this )
    {
        mOwner    = context.mOwner;
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


void HbLogContext::print( HbLogger::Level level, const char * message, ... ) const
{
    if( message )
    {
        va_list args;
        va_start( args, message );
        HbLogService::logger()->print( level, *this, message, args );
        va_end( args );
    }
}

void HbLogContext::system( HbLogger::Level level, const char * message, ... ) const
{
    if( message )
    {
        va_list args;
        va_start( args, message );
        HbLogService::logger()->system( level, *this, message, args );
        va_end( args );
    }
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
