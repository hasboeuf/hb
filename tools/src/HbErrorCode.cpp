#include <HbErrorCode.h>


bool HbErrorCode::add( qint32 code, const QString & message )
{
    if( !_errors.contains( code ) )
        if( !message.isEmpty() )
        {
            _errors.insert( code, message );
            return true;
        }

    return false;
}

QString HbErrorCode::get( qint32 code ) const
{
    if( !_errors.contains( code ) )
        Q_UNREACHABLE();

    return _errors.value( code );
}
