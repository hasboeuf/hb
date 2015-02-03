// Local
#include <contract/auth/HbAuthRequestContract.h>
#include <contract/HbNetworkProtocol.h>

HbAuthRequestContract::HbAuthRequestContract() :
    HbNetworkContract( HbNetworkProtocol::SERVICE_AUTH, HbNetworkProtocol::CODE_AUTH_REQUEST )
{

}

HbAuthRequestContract::HbAuthRequestContract( const HbAuthRequestContract & source ) :
    HbNetworkContract( source )
{
    if( & source != this )
    {
        mUsername = source.mUsername;
        mPassword = source.mPassword;
    }
}

HbAuthRequestContract & HbAuthRequestContract::operator=( const HbAuthRequestContract & source )
{
    if( &source != this )
    {
        HbNetworkContract::operator=( source );

        mUsername = source.mUsername;
        mPassword = source.mPassword;
    }

    return ( *this );
}

HbAuthRequestContract * HbAuthRequestContract::create() const
{
    return new HbAuthRequestContract();
}

bool HbAuthRequestContract::read( QDataStream & stream )
{
    stream >> mUsername;
    stream >> mPassword;

    return true;
}

bool HbAuthRequestContract::write( QDataStream & stream ) const
{
    stream << mUsername;
    stream << mPassword;

    return true;
}

QString HbAuthRequestContract::username() const
{
    return mUsername;
}

QString HbAuthRequestContract::passwork() const
{
    return mPassword;
}

void HbAuthRequestContract::setUsername( QString username )
{
    mUsername = username;
}

void HbAuthRequestContract::setPassword( QString password )
{
    mPassword = password;
}



