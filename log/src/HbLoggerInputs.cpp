// Hb
#include <HbLoggerInputs.h>
#include <HbLoggerPool.h>
#include <HbLogManager.h>

using namespace hb::log;


HbLoggerInputs::HbLoggerInputs( HbLogManager * parent ) :
    HbLoggerStream( parent )
{
    mpPool = parent->pool();
}


bool HbLoggerInputs::addTcpSocketInput( quint32 id, quint32 port )
{
    return mpPool->addTcpSocketInput( id, port );
}

bool HbLoggerInputs::addLocalSocketInput( quint32 id, const QString & name )
{
    return mpPool->addLocalSocketInput( id, name );
}

bool HbLoggerInputs::removeInput( quint32 id )
{
    return mpPool->removeInput( id );
}

IHbLoggerInput * HbLoggerInputs::input( quint32 id )
{
    return mpPool->input( id );
}
