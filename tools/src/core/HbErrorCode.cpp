#include <HbErrorCode.h>


bool HbErrorCode::add( qint32 code, const QString & message )
{
    if( !mErrors.contains( code ) )
        if( !message.isEmpty() )
        {
            mErrors.insert( code, message );
            return true;
        }

    return false;
}

QString HbErrorCode::get( qint32 code ) const
{
    if( !mErrors.contains( code ) )
        Q_UNREACHABLE();

    return mErrors.value( code );
}
