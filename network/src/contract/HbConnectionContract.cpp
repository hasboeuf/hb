// Local
#include <contract/HbConnectionContract.h>
#include <contract/HbNetworkProtocol.h>

HbConnectionContract::HbConnectionContract() :
    HbNetworkContract( HbNetworkProtocol::SERVICE_AUTH, HbNetworkProtocol::CODE_CONNECTION_REQUEST )
{

}

HbConnectionContract::HbConnectionContract( const HbConnectionContract & source ) :
    HbNetworkContract( source )
{
    if( & source != this )
    {
        mUsername = source.mUsername;
        mPassword = source.mPassword;
    }
}

HbConnectionContract & HbConnectionContract::operator=( const HbConnectionContract & source )
{
    if( &source != this )
    {
        HbNetworkContract::operator=( source );

        mUsername = source.mUsername;
        mPassword = source.mPassword;
    }

    return ( *this );
}

HbConnectionContract * HbConnectionContract::create() const
{
    return new HbConnectionContract();
}

bool HbConnectionContract::read( QDataStream & stream )
{
    stream >> mUsername;
    stream >> mPassword;

    return true;
}

bool HbConnectionContract::write( QDataStream & stream ) const
{
    stream << mUsername;
    stream << mPassword;

    return true;
}

QString HbConnectionContract::username() const
{
    return mUsername;
}

QString HbConnectionContract::passwork() const
{
    return mPassword;
}

void HbConnectionContract::setUsername( QString username )
{
    mUsername = username;
}

void HbConnectionContract::setPassword( QString password )
{
    mPassword = password;
}



