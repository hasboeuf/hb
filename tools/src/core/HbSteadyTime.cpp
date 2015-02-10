// Local
#include <core/HbSteadyTime.h>

using namespace hb::tools;

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

HbSteadyTime HbSteadyTime::fromDataTime( const QDateTime & datatime, quint64 steady )
{
    HbSteadyTime steady_time;
    steady_time.mDateTime = datatime;
    steady_time.mSteady   = steady;

    return steady_time;
}

HbSteadyTime HbSteadyTime::fromString( const QString & format, const QString & value )
{
    HbSteadyTime steady_time;
/*
    // Get steady part.
    if( format.length() != value.length() )
    {
        steady_time.mSteady = 0;
        return steady_time;
    }

    QString steady;
    for( int i = 0; i < format.length(); ++i )
    {
        if( format[i] == 'u' )
        {
            steady += value[i];
        }
    }
    steady_time.mSteady = steady.toInt();

    QString format_copy = format;
    format_copy.replace( "u", "" );

    // Get datetime part.
    steady_time.mDateTime = QDateTime::fromString( value, format );
*/
    return steady_time;
}

QString HbSteadyTime::toString( const QString & format )
{
    QString time_str = mDateTime.time().toString( format );

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
