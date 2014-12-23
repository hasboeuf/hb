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

bool HbLoggerOutputs::addConsoleOutput( quint32 id )
{
    return mpPool->addConsoleOutput( id );
}

bool HbLoggerOutputs::addGuiOutput( quint32 id, HbLogGuiNotifier * notifier )
{
    return mpPool->addGuiOutput( id, notifier );
}

bool HbLoggerOutputs::addFileOutput( quint32 id, const QString & file, quint32 max_size )
{
    return mpPool->addFileOutput( id, file, max_size );
}

bool HbLoggerOutputs::addTcpSocketOutput( quint32 id, const QString & ip, quint32 port )
{
    return mpPool->addTcpSocketOutput( id, ip, port );
}

bool HbLoggerOutputs::addLocalSocketOutput( quint32 id, const QString & name )
{
    return mpPool->addLocalSocketOutput( id, name );
}

bool HbLoggerOutputs::removeOutput( quint32 id )
{
    return mpPool->removeOutput( id );
}

IHbLoggerOutput * HbLoggerOutputs::output( quint32 id )
{
    return mpPool->output( id );
}
