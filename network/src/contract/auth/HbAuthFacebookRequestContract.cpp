// Local
#include <contract/auth/HbAuthFacebookRequestContract.h>
#include <contract/HbNetworkProtocol.h>
#include <service/auth/HbAuthService.h>

using namespace hb::network;

HbAuthFacebookRequestContract::HbAuthFacebookRequestContract() :
    HbAuthRequestContract()
{
    mType = HbAuthService::AUTH_FACEBOOK;
}

HbAuthFacebookRequestContract::HbAuthFacebookRequestContract( const HbAuthFacebookRequestContract & source ) :
    HbAuthRequestContract( source )
{
    if( & source != this )
    {
        mClient = source.mClient;
    }
}

HbAuthFacebookRequestContract & HbAuthFacebookRequestContract::operator=( const HbAuthFacebookRequestContract & source )
{
    if( &source != this )
    {
        HbAuthRequestContract::operator=( source );

        mClient = source.mClient;
    }

    return ( *this );
}

HbAuthFacebookRequestContract * HbAuthFacebookRequestContract::create() const
{
    return new HbAuthFacebookRequestContract();
}

bool HbAuthFacebookRequestContract::read( QDataStream & stream )
{
    HbAuthRequestContract::read( stream );
    mClient.read( stream );

    return true;
}

bool HbAuthFacebookRequestContract::write( QDataStream & stream ) const
{
    HbAuthRequestContract::write( stream );
    mClient.write( stream );

    return true;
}

const HbO2ClientFacebook & HbAuthFacebookRequestContract::client() const
{
    return mClient;
}

void HbAuthFacebookRequestContract::setClient( const HbO2ClientFacebook & client )
{
    mClient = client;
}
