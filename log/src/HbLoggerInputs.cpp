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

loguid HbLoggerInputs::addUdpSocketInput( const QString & ip, quint16 port, QString * error )
{
    return mpPool->addUdpSocketInput( ip, port, error );
}

loguid HbLoggerInputs::addTcpSocketInput( quint16 port, QString * error )
{
    return mpPool->addTcpSocketInput( port, error );
}

loguid HbLoggerInputs::addLocalSocketInput( const QString & name, QString * error )
{
    return mpPool->addLocalSocketInput( name, error );
}

bool HbLoggerInputs::removeInput( loguid uid, QString * error )
{
    return mpPool->removeInput( uid, error );
}

IHbLoggerInput * HbLoggerInputs::input( loguid uid )
{
    return mpPool->input( uid );
}
