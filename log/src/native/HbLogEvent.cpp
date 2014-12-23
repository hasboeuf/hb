#include <native/HbLogEvent.h>

using namespace hb::log;


HbLogEvent::HbLogEvent()
{
    _file = nullptr;
    _line = -1;
    _function = nullptr;

    _level = QtDebugMsg;
}

HbLogEvent::HbLogEvent( const HbLogEvent & event ) :
    HbLogEvent()
{
    if( &event != this )
    {
        _file = ( event._file ) ? qstrdup( event._file ) : nullptr;
        _function = ( event._function ) ? qstrdup( event._function ) : nullptr;
        _line = event._line;

        _level = event._level;
        _message = event._message;
    }
}

HbLogEvent::HbLogEvent( QtMsgType level, const QString & message ) :
    HbLogEvent()
{
    _level = level;
    _message = message;
}

HbLogEvent::HbLogEvent( QtMsgType level, const char * file, qint32 line, const char * function, const QString & message ) :
    HbLogEvent()
{
    if( file ) _file = qstrdup( file );
    if( function ) _function = qstrdup( function );
    _line = ( file ) ? line : -1;

    _level = level;
    _message = message;
}

HbLogEvent::~HbLogEvent()
{
    if( _file ) delete[] _file;
    if( _function ) delete[] _function;
}


HbLogEvent & HbLogEvent::operator =( const HbLogEvent & event )
{
    if( &event != this )
    {
        _file = ( event._file ) ? qstrdup( event._file ) : nullptr;
        _function = ( event._function ) ? qstrdup( event._function ) : nullptr;
        _line = event._line;

        _level = event._level;
        _message = event._message;
    }

    return *this;
}


const char * HbLogEvent::file() const
{
    return _file;
}

qint32 HbLogEvent::line() const
{
    return _line;
}

const char * HbLogEvent::function() const
{
    return _function;
}


QtMsgType HbLogEvent::level() const
{
    return _level;
}

const QString & HbLogEvent::message() const
{
    return _message;
}
