// Local
#include <contract/presence/HbPresenceContract.h>
#include <contract/HbNetworkProtocol.h>

HbPresenceContract::HbPresenceContract() :
    HbNetworkContract( HbNetworkProtocol::SERVICE_PRESENCE, HbNetworkProtocol::CODE_PRESENCE )
{

}

HbPresenceContract::HbPresenceContract( const HbPresenceContract & source ) :
    HbNetworkContract( source )
{
    if( & source != this )
    {

    }
}

HbPresenceContract & HbPresenceContract::operator=( const HbPresenceContract & source )
{
    if( &source != this )
    {
        HbNetworkContract::operator=( source );


    }

    return ( *this );
}

HbPresenceContract * HbPresenceContract::create() const
{
    return new HbPresenceContract();
}

bool HbPresenceContract::read( QDataStream & stream )
{


    return true;
}

bool HbPresenceContract::write( QDataStream & stream ) const
{


    return true;
}


