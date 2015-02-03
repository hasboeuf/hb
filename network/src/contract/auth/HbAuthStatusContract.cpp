// Local
#include <contract/auth/HbAuthStatusContract.h>
#include <contract/HbNetworkProtocol.h>

HbAuthStatusContract::HbAuthStatusContract() :
    HbNetworkContract( HbNetworkProtocol::SERVICE_AUTH, HbNetworkProtocol::CODE_AUTH_STATUS )
{

}

HbAuthStatusContract::HbAuthStatusContract( const HbAuthStatusContract & source ) :
    HbNetworkContract( source )
{
    if( & source != this )
    {

    }
}

HbAuthStatusContract & HbAuthStatusContract::operator=( const HbAuthStatusContract & source )
{
    if( &source != this )
    {
        HbNetworkContract::operator=( source );


    }

    return ( *this );
}

HbAuthStatusContract * HbAuthStatusContract::create() const
{
    return new HbAuthStatusContract();
}

bool HbAuthStatusContract::read( QDataStream & stream )
{


    return true;
}

bool HbAuthStatusContract::write( QDataStream & stream ) const
{


    return true;
}


