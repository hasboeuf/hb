// Hb
#include <HbLoggerOutputs.h>
#include <HbLoggerPool.h>
#include <HbLogManager.h>

using namespace hb::log;


HbLoggerOutputs::HbLoggerOutputs( HbLogManager * parent ) :
    HbLoggerStream( parent )
{
    mpPool = parent->pool();
}

loguid HbLoggerOutputs::addConsoleOutput( QString * error )
{
    return mpPool->addConsoleOutput( error );
}

loguid HbLoggerOutputs::addGuiOutput(HbLogGuiNotifier * notifier, QString * error )
{
    return mpPool->addGuiOutput( notifier, error );
}

loguid HbLoggerOutputs::addFileOutput(const QString & dir, quint32 max_size, QString * error )
{
    return mpPool->addFileOutput( dir, max_size, error );
}

loguid HbLoggerOutputs::addUdpSocketOutput( quint16 port, QString * error )
{
    return mpPool->addUdpSocketOutput( port, error );
}

loguid HbLoggerOutputs::addTcpSocketOutput( const QString & ip, quint16 port, QString * error )
{
    return mpPool->addTcpSocketOutput( ip, port, error );
}

loguid HbLoggerOutputs::addLocalSocketOutput( const QString & name, QString * error )
{
    return mpPool->addLocalSocketOutput( name, error );
}

bool HbLoggerOutputs::removeOutput( loguid id, QString * error )
{
    return mpPool->removeOutput( id, error );
}

IHbLoggerOutput * HbLoggerOutputs::output( loguid id )
{
    return mpPool->output( id );
}
