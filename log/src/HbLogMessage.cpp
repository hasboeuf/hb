// Qt
#include <QtCore/QTime>
// Hb
#include <HbLogMessage.h>

using namespace hb::log;

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

        QTime  time    = QTime::fromString( time_str, QStringLiteral( "HH:mm:ss:zzz" ) );
        qint32 timetag = time.msec() + 1000 * ( time.second() + ( time.minute() * 60 ) + ( time.hour() * 3600 ) );
        qint32 line    = ( qint32 ) line_str.toInt();

        HbLogContext context( owner, file.toStdString().c_str(), line, function.toStdString().c_str() );
        msg = new HbLogMessage( level, HbLogger::OUTPUT_ALL, context, timetag, text );
    }

    return msg;
}

const QString HbLogMessage::toRaw(const HbLogMessage &msg)
{
    QString raw;

    raw += msg.levelStr( false )                             + HbLogMessage::msFieldSeparator;
    raw += msg.timeTagStr()                                  + HbLogMessage::msFieldSeparator;
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
    mTimeTag   = -1;
}

HbLogMessage::HbLogMessage( HbLogger::Level level, HbLogger::Formats format,
                            const HbLogContext & context, qint32 timeTag, const QString & message ) :
	QObject()
{
    mLevel   = level;
    mFormat  = format;
    mContext = context;
    mTimeTag = timeTag;
	mMessage = message;
}

HbLogMessage::HbLogMessage( const HbLogMessage & message ) :
    HbLogMessage()
{
    if( &message != this )
    {
        mLevel = message.mLevel;
        mFormat = message.mFormat;
        mContext = message.mContext;
        mTimeTag = message.mTimeTag;
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
        mTimeTag = message.mTimeTag;
        mMessage = message.mMessage;
    }

    return *this;
}


bool HbLogMessage::system() const
{
    return mFormat.testFlag( HbLogger::OUTPUT_SYSTEM );
}

HbLogger::Level HbLogMessage::level() const
{
    return mLevel;
}

QString HbLogMessage::levelStr(bool spacing) const
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

qint32 HbLogMessage::timeTag() const
{
    return mTimeTag;
}

QString HbLogMessage::timeTagStr() const
{
    return QStringLiteral( "%1" ).arg( QTime( 0, 0 ).
        addMSecs( mTimeTag ).toString( QStringLiteral( "HH:mm:ss:zzz" ) ) );
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
        if( mTimeTag > 0 )
        {
            buffer += QStringLiteral( "[%1]" ).arg( timeTagStr() );
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
    stream << mTimeTag;
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
	stream >> mTimeTag;
	stream >> mMessage;

    mLevel = ( HbLogger::Level ) enum_stream;
}
