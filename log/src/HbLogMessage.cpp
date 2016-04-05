// Qt
#include <QtCore/QTime>
// Hb
#include <HbLogMessage.h>
#include <core/HbSteadyDateTime.h>

using namespace hb::log;
using namespace hb::tools;

const QString HbLogMessage::msFieldSeparator = QStringLiteral( "___" );

const HbLogMessage * HbLogMessage::fromRaw( const QString & raw)
{
    HbLogMessage * msg = nullptr;

    QStringList fields = raw.split( msFieldSeparator );
    if( fields.size() == 7)
    {
        QString level_str   = fields.at( 0 );
        QString time_str    = fields.at( 1 );
        QString owner       = fields.at( 2 );
        QString line_str    = fields.at( 3 );
        QString file        = fields.at( 4 );
        QString function    = fields.at( 5 );
        QString text        = fields.at( 6 );

        HbLogger::Level level = HbLogger::MetaLevel::fromString( level_str, HbLogger::LEVEL_NONE );

        HbSteadyDateTime datetime = HbSteadyDateTime::fromString( QStringLiteral( "yyyy-MM-dd-HH:mm:ss:zzz.uuuuuu" ), time_str );
        qint64 timestamp = datetime.toNsSinceEpoch();
        qint32 line    = ( qint32 ) line_str.toInt();

        HbLogContext context( owner, file.toStdString().c_str(), line, function.toStdString().c_str() );
        msg = new HbLogMessage( level, HbLogger::OUTPUT_ALL, context, timestamp, text );
    }

    return msg;
}

QString HbLogMessage::toRaw(const HbLogMessage &msg)
{
    QString raw;

    raw += msg.levelStr( false )                             + HbLogMessage::msFieldSeparator;
    raw += HbSteadyDateTime::fromNsSinceEpoch( msg.timestamp() ).toString( "yyyy-MM-dd-HH:mm:ss:zzz.uuuuuu" )
                                                             + HbLogMessage::msFieldSeparator;
    raw += msg.mContext.owner()                              + HbLogMessage::msFieldSeparator;
    raw += QStringLiteral( "%1" ).arg( msg.mContext.line() ) + HbLogMessage::msFieldSeparator;
    raw += msg.mContext.file()                               + HbLogMessage::msFieldSeparator;
    raw += msg.mContext.function()                           + HbLogMessage::msFieldSeparator;
    raw += msg.mMessage;

    return raw;
}

HbLogMessage::HbLogMessage() :
    QObject()
{
    mLevel     = HbLogger::LEVEL_NONE;
    mFormat    = HbLogger::OUTPUT_ALL;
    mTimestamp = 0;
}

HbLogMessage::HbLogMessage(HbLogger::Level level, HbLogger::Formats format,
                            const HbLogContext & context, qint64 timestamp, const QString & message ) :
    QObject()
{
    mLevel     = level;
    mFormat    = format;
    mContext   = context;
    mTimestamp = timestamp;
    mMessage   = message;
}

HbLogMessage::HbLogMessage( const HbLogMessage & message ) :
    HbLogMessage()
{
    if( &message != this )
    {
        mLevel = message.mLevel;
        mFormat = message.mFormat;
        mContext = message.mContext;
        mTimestamp = message.mTimestamp;
        mMessage = message.mMessage;
    }
}


HbLogMessage & HbLogMessage::operator =( const HbLogMessage & message )
{
    if( &message != this )
    {
        mLevel = message.mLevel;
        mFormat = message.mFormat;
        mContext = message.mContext;
        mTimestamp = message.mTimestamp;
        mMessage = message.mMessage;
    }

    return *this;
}

HbLogger::Level HbLogMessage::level() const
{
    return mLevel;
}

QString HbLogMessage::levelStr( bool spacing ) const
{
    QString level = HbLogger::MetaLevel::toString( mLevel );
    if( spacing )
    {
        level = level.leftJustified( 14, QChar::Space ); // LEVEL_CRITICAL is the longest.
    }
    return level;
}

const HbLogContext & HbLogMessage::context() const
{
    return mContext;
}

qint64 HbLogMessage::timestamp() const
{
    return mTimestamp;
}

QString HbLogMessage::timestampStr() const
{
    return HbSteadyDateTime::fromNsSinceEpoch( mTimestamp ).toString("HH:mm:ss.zzz.uuuuuu");
}

const QString & HbLogMessage::message() const
{
    return mMessage;
}


QString HbLogMessage::toString() const
{
    QString buffer;

    if( mFormat & HbLogger::OUTPUT_LEVEL )
    {
        buffer += levelStr();
    }

    if( mFormat & HbLogger::OUTPUT_TIME )
    {
        if( mTimestamp > 0 )
        {
            buffer += QStringLiteral( "[%1]" ).arg( timestampStr() );
        }
    }

    if( mFormat & HbLogger::OUTPUT_WHO )
    {
        buffer += QStringLiteral( "[%1]" ).arg( mContext.owner() );
    }

    if( mFormat & HbLogger::OUTPUT_WHERE )
    {
        if( !mContext.file().isEmpty() )
        {
            buffer += QStringLiteral( "[%1::%2 (line %3)]" ).arg( mContext.file() ).
                arg( mContext.function() ).arg( mContext.line() );
        }
    }

    if( mFormat & HbLogger::OUTPUT_TEXT )
    {
        buffer += QStringLiteral( " %1" ).arg( mMessage );
    }

    return buffer;
}


QByteArray HbLogMessage::toByteArray() const
{
    QByteArray packet;
    QDataStream stream( &packet, QIODevice::WriteOnly );

    qint32 size = 0;

    stream << size;
    stream << ( qint32 ) mLevel;
    stream << mContext;
    stream << mTimestamp;
    stream << mMessage;

    stream.device()->seek( 0 );

    size = packet.size() - sizeof( qint32 );
    stream << size;

    return packet;
}

void HbLogMessage::fromDataStream( QDataStream & stream )
{
    // ASB: How to test the integrity of the stream?
    qint32 enum_stream = 0;

    stream >> enum_stream;
    stream >> mContext;
    stream >> mTimestamp;
    stream >> mMessage;

    mLevel = ( HbLogger::Level ) enum_stream;
}
