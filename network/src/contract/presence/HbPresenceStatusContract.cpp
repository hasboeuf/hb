// Local
#include <contract/presence/HbPresenceStatusContract.h>
#include <contract/HbNetworkProtocol.h>

HbPresenceStatusContract::HbPresenceStatusContract() :
    HbNetworkContract( HbNetworkProtocol::SERVICE_PRESENCE,
                       HbNetworkProtocol::CODE_SRV_PRESENCE_STATUS )
{
    setRouting( HbNetworkProtocol::ROUTING_MULTICAST );
}

HbPresenceStatusContract::HbPresenceStatusContract( const HbPresenceStatusContract & source ) :
    HbNetworkContract( source )
{
    if( & source != this )
    {

    }
}

HbPresenceStatusContract & HbPresenceStatusContract::operator=( const HbPresenceStatusContract & source )
{
    if( &source != this )
    {
        HbNetworkContract::operator=( source );
    }

    return ( *this );
}

HbPresenceStatusContract * HbPresenceStatusContract::create() const
{
    return new HbPresenceStatusContract();
}

bool HbPresenceStatusContract::read( QDataStream & stream )
{
    Q_UNUSED( stream )

    return true;
}

bool HbPresenceStatusContract::write( QDataStream & stream ) const
{
    Q_UNUSED( stream )

    return true;
}


