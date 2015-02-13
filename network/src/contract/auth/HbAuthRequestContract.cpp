// Local
#include <contract/auth/HbAuthRequestContract.h>
#include <contract/HbNetworkProtocol.h>
#include <service/auth/HbAuthService.h>

using namespace hb::network;

HbAuthRequestContract::HbAuthRequestContract() :
    HbNetworkContract( HbNetworkProtocol::SERVICE_AUTH, HbNetworkProtocol::CODE_CLT_AUTH_REQUEST )
{
    mType = HbAuthService::AUTH_NONE;
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

bool HbAuthRequestContract::read( QDataStream & stream )
{
    quint8 type;
    stream >> type;

    mType = ( HbAuthService::AuthType ) type;

    return true;
}

bool HbAuthRequestContract::write( QDataStream & stream ) const
{
    stream << ( qint32 ) mType;

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


