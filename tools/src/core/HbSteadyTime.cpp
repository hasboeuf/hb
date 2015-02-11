// Qt
#include <QtCore/QDebug>
// Local
#include <core/HbSteadyTime.h>

using namespace hb::tools;

HbSteadyTime::HbSteadyTime()
{
    mSteady = 0;
}

HbSteadyTime HbSteadyTime::now()
{
    system_clock::time_point::duration system_time   = system_clock::now().time_since_epoch();
    steady_clock::time_point::duration accurate_time = steady_clock::now().time_since_epoch();

    quint64 timestamp = duration_cast< milliseconds > ( system_time ).count();

    quint64 steady    = ( accurate_time - duration_cast< milliseconds >( accurate_time ) ).count();

    HbSteadyTime current_time;
    current_time.mDateTime = QDateTime::fromMSecsSinceEpoch( timestamp );
    current_time.mSteady = steady;

    return current_time;
}

HbSteadyTime HbSteadyTime::fromDateTime( const QDateTime & datetime, quint64 steady )
{
    HbSteadyTime steady_time;
    steady_time.mDateTime = datetime;
    steady_time.mSteady   = steady;

    if( !steady_time.mDateTime.isValid() ) qDebug() << "fromDateTime: Invalid datetime!";

    return steady_time;
}

HbSteadyTime HbSteadyTime::fromString( const QString & format, const QString & value )
{
    HbSteadyTime steady_time;

    if( format.length() != value.length() )
    {
        return steady_time;
    }

    // Get steady part.
    QString value_copy = value;
    QString steady;
    for( int i = 0; i < format.length(); ++i )
    {
        if( format[i] == 'u' )
        {
            steady += value[i];
            value_copy[i] = 'u'; // QDateTime::fromString wants format and value coherent.
        }
    }
    steady_time.mSteady = steady.toInt();

    // Get datetime part.
    qDebug() << "value_copy=" << value_copy << " format=" << format;
    steady_time.mDateTime = QDateTime::fromString( value_copy, format );

    if( !steady_time.mDateTime.isValid() ) qDebug() << "fromString: Invalid datetime!";

    return steady_time;
}

HbSteadyTime HbSteadyTime::fromNsSinceEpoch( qint64 nano )
{
    HbSteadyTime steady_time;
    qDebug() << "epoch=" << nano;
    qint64 ms = nano * pow( 10, -6 );
    qDebug() << "epoch_ms=" << ms;
    steady_time.mDateTime = QDateTime::fromMSecsSinceEpoch( ms );
    steady_time.mSteady = ( nano - ms * pow( 10, 6 ) );
    qDebug() << "steady=" << steady_time.mSteady;

    if( !steady_time.mDateTime.isValid() ) qDebug() << "fromNsSinceEpoch: Invalid datetime!";
    return steady_time;
}

qint64 HbSteadyTime::toNsSinceEpoch() const
{
    if( !mDateTime.isValid() ) qDebug() << "toNsSinceEpoch: Invalid datetime!";
    qint64 timestamp = mDateTime.toMSecsSinceEpoch();
    qDebug() << "timestamp_str=" << mDateTime.toString("hh:mm:ss.zzz");
    qint64 ns        = mSteady;

    qDebug() << "timestamp=" << timestamp;
    qDebug() << "ns=" << ns;

    timestamp *= pow( 10, 6 ); // ms to ns.
    timestamp += ns;

    qDebug() << "timestampns=" << timestamp;

    return timestamp;
}

QString HbSteadyTime::toString( const QString & format )
{

    QString time_str;

    // Stringify datetime.
    time_str += mDateTime.time().toString( format );

    // Stringify steady part.
    QString steady = QString::number( mSteady );
    steady.rightJustified( 6, '0' );
    quint32 u_max  = steady.length();
    quint32 u_nb   = 0;
    for( int i = 0; i < format.length(); ++i )
    {
        if( format[i] == 'u' )
        {
            if( u_nb <= u_max )
            {
                time_str.replace( i, 1, steady[u_nb++] );
            }
        }
        else
        {
            u_nb = 0;
        }
    }

    return time_str;
}

const QDateTime & HbSteadyTime::datetime() const
{
    return mDateTime;
}

quint64 HbSteadyTime::steady() const
{
    return mSteady;
}
