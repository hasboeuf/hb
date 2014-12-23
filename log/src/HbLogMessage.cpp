// Qt
#include <QtCore/QTime>
// Hb
#include <HbLogMessage.h>

using namespace hb::log;


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

const HbLogContext & HbLogMessage::context() const
{
    return mContext;
}


QString HbLogMessage::timeTag() const
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

	if( mFormat & HbLogger::OUTPUTmLevel )
	{
		QString level = HbLogger::MetaLevel::toString( mLevel );
		buffer += level.leftJustified( 14, QChar::Space ); // LEVEL_CRITICAL is the longest.
	}

	if( mFormat & HbLogger::OUTPUT_TIME )
    {
        if( mTimeTag > 0 )
            buffer += QStringLiteral( "[%1]" ).arg( timeTag() );
	}

    if( mFormat & HbLogger::OUTPUT_WHO )
        buffer += QStringLiteral( "[%1]" ).arg( mContext.owner() );

    if( mFormat & HbLogger::OUTPUT_WHERE )
        if( !mContext.file().isEmpty() )
        {
            buffer += QStringLiteral( "[%1::%2 (line %3)]" ).arg( mContext.file() ).
                arg( mContext.function() ).arg( mContext.line() );
        }

	if( mFormat & HbLogger::OUTPUT_TEXT )
        buffer += QStringLiteral( " %1" ).arg( mMessage );

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
