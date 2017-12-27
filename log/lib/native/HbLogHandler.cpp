#include <native/HbLogHandler.h>

#include <HbGlobal.h>
#include <QCoreApplication>
#include <QMetaMethod>
#include <QThread>

using namespace hb::log;


HbLogHandler * HbLogHandler::_handler = nullptr;

HbLogHandler::HbLogHandler() :
    QObject()
{
    QCoreApplication * instance = QCoreApplication::instance();
    q_assert_x( instance, "HbLogHandler", "Qt application not defined" );

    qRegisterMetaType< hb::log::HbLogEvent >( "HbLogEvent" );

    connect( this, &HbLogHandler::print, 
        this, [=]( const HbLogEvent & event ) 
        { 
            if( instance )
                enqueue( event ); 

        }, Qt::UniqueConnection );

    connect( instance, &QObject::destroyed, this,
        [this]() { disconnect( this, &HbLogHandler::print, this, nullptr ); },
        static_cast< Qt::ConnectionType >( Qt::DirectConnection | Qt::UniqueConnection ) );
}


HbLogHandler * HbLogHandler::handler()
{
    if( !_handler )
    {
        Q_ASSERT( QThread::currentThread() == qApp->thread() );
        _handler = q_check_ptr( new HbLogHandler() );
    }

    return _handler;
}


HbLogEvent HbLogHandler::dequeue( QtMsgType type )
{
    Q_ASSERT( QThread::currentThread() == qApp->thread() );

    switch( type )
    {
        case QtDebugMsg :
            return _debugs.dequeue();

        case QtWarningMsg :
            return _warnings.dequeue();

        case QtCriticalMsg :
            return _errors.dequeue();

        case QtFatalMsg :
            return _criticals.dequeue();

        default :

            Q_UNREACHABLE();
            return HbLogEvent();
    }
}

bool HbLogHandler::availables( QtMsgType type ) const
{
    switch( type )
    {
        case QtDebugMsg :
            return ( !_debugs.isEmpty() );

        case QtWarningMsg :
            return ( !_warnings.isEmpty() );

        case QtCriticalMsg :
            return ( !_errors.isEmpty() );

        case QtFatalMsg :
            return ( !_criticals.isEmpty() );

        default :

            Q_UNREACHABLE();
            return false;
    }
}


void HbLogHandler::enqueue( const HbLogEvent & event )
{
    Q_ASSERT( QThread::currentThread() == qApp->thread() );

    if( !event.message().isEmpty() )
    {
        switch( event.level() )
        {
            case QtDebugMsg :

                _debugs.enqueue( event );
                break;

            case QtWarningMsg :

                _warnings.enqueue( event );
                break;

            case QtCriticalMsg :

                _errors.enqueue( event );
                break;

            case QtFatalMsg :

                _criticals.enqueue( event );
                break;

            default :

                Q_UNREACHABLE();
                break;
        }

        emit logEvent( event.level() );
    }
}

void HbLogHandler::connectNotify( const QMetaMethod & signal )
{
    Q_ASSERT( QThread::currentThread() == qApp->thread() );
    QByteArray event = QMetaObject::normalizedSignature( SIGNAL( logEvent( QtMsgType ) ) );

    if( signal == QMetaMethod::fromSignal( &HbLogHandler::logEvent ) )
    {
        if( !_criticals.isEmpty() )
            emit logEvent( QtFatalMsg );

        if( !_errors.isEmpty() )
            emit logEvent( QtCriticalMsg );

        if( !_warnings.isEmpty() )
            emit logEvent( QtWarningMsg );

        if( !_debugs.isEmpty() )
            emit logEvent( QtDebugMsg );
    }
}