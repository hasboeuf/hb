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

HbSteadyTime HbSteadyTime::fromDateTime( const QDateTime & datatime, quint64 steady )
{
    HbSteadyTime steady_time;
    steady_time.mDateTime = datatime;
    steady_time.mSteady   = steady;

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
    steady_time.mDateTime = QDateTime::fromString( value_copy, format );


    return steady_time;
}

HbSteadyTime HbSteadyTime::fromEpoch( quint64 nano )
{
    HbSteadyTime steady_time;

    QString time = QString::number( nano );

    steady_time.mDateTime = QDateTime::fromMSecsSinceEpoch( time.left( time.size() - 6 ).toInt() );
    steady_time.mSteady   = time.right( 6 ).toInt();

    return steady_time;
}

quint64 HbSteadyTime::sinceEpoch() const
{
    QString time;
    time.append( QString::number( mDateTime.toMSecsSinceEpoch() ) );
    time.append( QString::number( mSteady ) );
    return time.toInt();
}

QString HbSteadyTime::toString( const QString & format )
{

    QString time_str;

    // Stringify datetime.
    time_str += mDateTime.time().toString( format );

    // Stringify steady part.
    QString steady = QString::number( mSteady );
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
