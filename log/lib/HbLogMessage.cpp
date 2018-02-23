// Qt
#include <QtCore/QTime>
// Hb
#include <HbLogMessage.h>
#include <core/HbSteadyDateTime.h>

using namespace hb::log;
using namespace hb::tools;

static constexpr char TOKEN_LEVEL[] = "%{level}";
static constexpr char TOKEN_TIME[] = "%{time}";
static constexpr char TOKEN_APP[] = "%{app}";
static constexpr char TOKEN_FILE[] = "%{file}";
static constexpr char TOKEN_FUNCTION[] = "%{function}";
static constexpr char TOKEN_LINE[] = "%{line}";
static constexpr char TOKEN_MESSAGE[] = "%{message}";

const QString HbLogMessage::msFieldSeparator = QStringLiteral( "___" );
QString HbLogMessage::msPattern = "%{level} %{time} %{app} %{file} %{function} %{line} %{message}";
HbLogMessage::Outputs HbLogMessage::msOutputs = HbLogMessage::OUTPUT_ALL;

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

        HbLogger::Level level = HbLogger::MetaLevel::fromString( level_str );

        HbSteadyDateTime datetime = HbSteadyDateTime::fromString( time_str, QStringLiteral( "yyyy-MM-dd-HH:mm:ss:zzz.uuuuuu" ) );
        qint64 timestamp = datetime.toNsSinceEpoch();
        qint32 line    = ( qint32 ) line_str.toInt();

        HbLogContext context;
        context.setOwner( owner );
        context.setFile( file );
        context.setFunction( function );
        context.setLine( line );
        msg = new HbLogMessage( level, context, timestamp, text );
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

void HbLogMessage::setPattern( const QString & pattern )
{
    if ( pattern.isEmpty() ) {
        return;
    }

    Outputs outputs = OUTPUT_NONE;
    if ( pattern.contains( TOKEN_LEVEL    ) ) outputs |= OUTPUT_LEVEL;
    if ( pattern.contains( TOKEN_TIME     ) ) outputs |= OUTPUT_TIME;
    if ( pattern.contains( TOKEN_APP      ) ) outputs |= OUTPUT_APP;
    if ( pattern.contains( TOKEN_FILE     ) ) outputs |= OUTPUT_FILE;
    if ( pattern.contains( TOKEN_FUNCTION ) ) outputs |= OUTPUT_FUNCTION;
    if ( pattern.contains( TOKEN_LINE     ) ) outputs |= OUTPUT_LINE;
    if ( pattern.contains( TOKEN_MESSAGE  ) ) outputs |= OUTPUT_MESSAGE;

    if ( outputs == OUTPUT_NONE ) {
        return;
    }

    HbLogMessage::msPattern = pattern;
    HbLogMessage::msOutputs = outputs;
}

HbLogMessage::HbLogMessage() :
    QObject()
{
    mLevel     = HbLogger::LEVEL_NONE;
    mTimestamp = 0;
}

HbLogMessage::HbLogMessage(HbLogger::Level level,
                            const HbLogContext & context, qint64 timestamp, const QString & message ) :
    QObject()
{
    mLevel     = level;
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
    QString buffer = HbLogMessage::msPattern;

    if ( HbLogMessage::msOutputs & OUTPUT_LEVEL ) {
        buffer.replace( TOKEN_LEVEL, levelStr( true ) );
    }

    if ( HbLogMessage::msOutputs & OUTPUT_TIME ) {
        buffer.replace( TOKEN_TIME, timestampStr() );
    }

    if ( HbLogMessage::msOutputs & OUTPUT_APP ) {
        buffer.replace( TOKEN_APP, mContext.owner() );
    }

    if ( HbLogMessage::msOutputs & OUTPUT_FILE ) {
        buffer.replace( TOKEN_FILE, mContext.file() );
    }

    if ( HbLogMessage::msOutputs & OUTPUT_FUNCTION ) {
        buffer.replace( TOKEN_FUNCTION, mContext.function() );
    }

    if ( HbLogMessage::msOutputs & OUTPUT_LINE ) {
        buffer.replace( TOKEN_LINE, QString::number( mContext.line() ) );
    }

    if ( HbLogMessage::msOutputs & OUTPUT_MESSAGE ) {
        buffer.replace( TOKEN_MESSAGE, mMessage );
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
