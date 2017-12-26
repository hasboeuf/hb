// Local
#include <contract/auth/HbAuthRequestContract.h>
#include <contract/HbNetworkProtocol.h>
#include <service/auth/HbAuthService.h>

using namespace hb::network;

HbAuthRequestContract::HbAuthRequestContract() :
    HbNetworkContract( HbNetworkProtocol::SERVICE_AUTH,
                       HbNetworkProtocol::CODE_CLT_AUTH_REQUEST )
{
    setRouting( HbNetworkProtocol::ROUTING_UNICAST );
    mType   = HbAuthService::AUTH_NONE;
    mpReply = new HbAuthStatusContract();
}

HbAuthRequestContract::HbAuthRequestContract( const HbAuthRequestContract & source ) :
    HbNetworkContract( source )
{
    if( & source != this )
    {
        mType = source.mType;
    }
}

HbAuthRequestContract & HbAuthRequestContract::operator=( const HbAuthRequestContract & source )
{
    if( &source != this )
    {
        HbNetworkContract::operator=( source );

        mType = source.mType;
    }

    return ( *this );
}

HbAuthRequestContract * HbAuthRequestContract::create() const
{
    return new HbAuthRequestContract();
}

HbAuthStatusContract * HbAuthRequestContract::takeReply() const
{
    return HbNetworkContract::takeReply()->value< HbAuthStatusContract >();
}


bool HbAuthRequestContract::read( QDataStream & stream )
{
    authstgy type;
    stream >> type;

    mType = ( HbAuthService::AuthType ) type;

    return true;
}

bool HbAuthRequestContract::write( QDataStream & stream ) const
{
    stream << ( authstgy ) mType;

    return true;
}

authstgy HbAuthRequestContract::type() const
{
    return mType;
}

void HbAuthRequestContract::setType( authstgy type )
{
    mType = type;
}


