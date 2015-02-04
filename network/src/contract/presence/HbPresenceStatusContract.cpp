// Local
#include <contract/presence/HbPresenceStatusContract.h>
#include <contract/HbNetworkProtocol.h>

HbPresenceStatusContract::HbPresenceStatusContract() :
    HbNetworkContract( HbNetworkProtocol::SERVICE_PRESENCE, HbNetworkProtocol::CODE_SRV_PRESENCE_STATUS )
{

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


    return true;
}

bool HbPresenceStatusContract::write( QDataStream & stream ) const
{


    return true;
}


