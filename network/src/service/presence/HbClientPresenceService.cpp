// Qt
#include <QtCore/QTimerEvent>
// Hb
#include <HbLogService.h>
// Local
#include <service/presence/HbClientPresenceService.h>
#include <contract/presence/HbPresenceContract.h>

using namespace hb::network;


HbClientPresenceService::HbClientPresenceService()
{
}

void HbClientPresenceService::reset()
{
    foreach( qint32 timer_id , mTimerBySocketUid )
    {
        killTimer( timer_id );
    }

    mTimerBySocketUid.clear();
    mSocketByTimerId.clear();
}

const HbServicePresenceClientConfig & HbClientPresenceService::config() const
{
    return mConfig;
}

void HbClientPresenceService::setConfig( const HbServicePresenceClientConfig & config )
{
    if( config.isValid() )
    {
        mConfig = config;
    }
}

void HbClientPresenceService::timerEvent( QTimerEvent * event )
{
    qint32 timer_id = event->timerId();

    networkuid socket_uid = mSocketByTimerId.value( timer_id, 0 );

    q_assert( socket_uid > 0 );

    HbPresenceContract * presence = new HbPresenceContract( );
    presence->addSocketReceiver( socket_uid );
    //emit readyContractToSend( presence );
}

void HbClientPresenceService::onSocketAuthenticated( networkuid socket_uid )
{
    q_assert( !mTimerBySocketUid.contains( socket_uid ) );

    HbInfo( "Socket authenticated, start keep alive timer." );
    qint32 timer_id = startTimer( mConfig.keepAliveInterval() * 1000 );

    mTimerBySocketUid.insert( socket_uid, timer_id );
    mSocketByTimerId.insert ( timer_id, socket_uid );
}

void HbClientPresenceService::onSocketUnauthenticated( networkuid socket_uid )
{
    qint32 timer_id = mTimerBySocketUid.value( socket_uid, 0 );
    if( timer_id > 0 )
    {
        HbInfo( "Socket unauthenticated, stop keep alive timer." );
        killTimer( timer_id );
        mSocketByTimerId.remove( timer_id );
    }

    mTimerBySocketUid.remove( socket_uid );
}

void HbClientPresenceService::onContractReceived( const HbNetworkContract * contract )
{
    Q_UNUSED( contract )
    // Useless.
}
