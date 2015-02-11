// Qt
#include <QtCore/QDebug>
// Local
#include <core/HbSteadyDateTime.h>

using namespace hb::tools;

HbSteadyDateTime::HbSteadyDateTime()
{
    mSteady = 0;
}

HbSteadyDateTime HbSteadyDateTime::now()
{
    // system_clock's epoch is 1st jan 70.
    // steady_clock's epoch is the last boot of the machine ( with gcc ).
    system_clock::time_point::duration system_time   = system_clock::now().time_since_epoch();
    steady_clock::time_point::duration accurate_time = steady_clock::now().time_since_epoch();

    qint64 timestamp = duration_cast< milliseconds > ( system_time ).count();

    // We only take the nano to milliseconds part.
    // e.g.: 564532413521[432132] ns -> steady = the bracket part.
    qint64 steady = ( accurate_time - duration_cast< milliseconds >( accurate_time ) ).count();

    HbSteadyDateTime current_time;
    current_time.mDateTime = QDateTime::fromMSecsSinceEpoch( timestamp );
    current_time.mSteady = steady;

    return current_time;
}

HbSteadyDateTime HbSteadyDateTime::fromDateTime( const QDateTime & datetime, quint64 steady )
{
    HbSteadyDateTime steady_time;
    steady_time.mDateTime = datetime;
    steady_time.mSteady   = steady;

    if( !steady_time.mDateTime.isValid() ) qDebug() << "fromDateTime: Invalid datetime!";

    return steady_time;
}

HbSteadyDateTime HbSteadyDateTime::fromString( const QString & format, const QString & value )
{
    HbSteadyDateTime steady_time;

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

    steady = steady.leftJustified( 6, '0' );
    steady_time.mSteady = steady.toInt();

    // Get datetime part.
    steady_time.mDateTime = QDateTime::fromString( value_copy, format );

    if( !steady_time.mDateTime.isValid() ) qDebug() << "Invalid datetime! Some fields missing?";

    return steady_time;
}

HbSteadyDateTime HbSteadyDateTime::fromNsSinceEpoch( qint64 nano )
{
    HbSteadyDateTime steady_time;
    qint64 ms = nano * pow( 10, -6 );

    steady_time.mDateTime = QDateTime::fromMSecsSinceEpoch( ms );
    steady_time.mSteady = ( nano - ms * pow( 10, 6 ) );

    if( !steady_time.mDateTime.isValid() ) qDebug() << "Invalid datetime!";
    return steady_time;
}

qint64 HbSteadyDateTime::toNsSinceEpoch() const
{
    if( !mDateTime.isValid() ) qDebug() << "Invalid datetime!";
    qint64 timestamp = mDateTime.toMSecsSinceEpoch();
    qint64 ns        = mSteady;

    timestamp *= pow( 10, 6 ); // ms to ns.
    timestamp += ns;

    return timestamp;
}

QString HbSteadyDateTime::toString( const QString & format )
{

    QString time_str;

    // Stringify datetime.
    time_str += mDateTime.toString( format );

    // Stringify steady part.
    QString steady = QString::number( mSteady );
    steady = steady.leftJustified( 6, '0' );
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

const QDateTime & HbSteadyDateTime::datetime() const
{
    return mDateTime;
}

quint64 HbSteadyDateTime::steady() const
{
    return mSteady;
}
