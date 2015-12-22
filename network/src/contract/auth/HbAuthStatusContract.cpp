// Local
#include <contract/auth/HbAuthStatusContract.h>
#include <contract/HbNetworkProtocol.h>

using namespace hb::network;

HbAuthStatusContract::HbAuthStatusContract() :
    HbNetworkContract( HbNetworkProtocol::SERVICE_AUTH,
                       HbNetworkProtocol::CODE_SRV_AUTH_STATUS )
{
    setRouting( HbNetworkProtocol::ROUTING_UNICAST );
    mStatus    = HbNetworkProtocol::AUTH_BAD;
    mTryNumber = 0;
    mMaxTries  = 0;
}

HbAuthStatusContract::HbAuthStatusContract( const HbAuthStatusContract & source ) :
    HbNetworkContract( source )
{
    if( & source != this )
    {
        mStatus      = source.mStatus;
        mDescription = source.mDescription;
        mTryNumber   = source.mTryNumber;
        mMaxTries    = source.mMaxTries;
        mUserInfo    = source.mUserInfo;
    }
}

HbAuthStatusContract & HbAuthStatusContract::operator=( const HbAuthStatusContract & source )
{
    if( &source != this )
    {
        HbNetworkContract::operator=( source );

        mStatus      = source.mStatus;
        mDescription = source.mDescription;
        mTryNumber   = source.mTryNumber;
        mMaxTries    = source.mMaxTries;
        mUserInfo    = source.mUserInfo;
    }

    return ( *this );
}

HbAuthStatusContract * HbAuthStatusContract::create() const
{
    return new HbAuthStatusContract();
}

bool HbAuthStatusContract::read( QDataStream & stream )
{
    netwint status;
    stream >> status;
    stream >> mDescription;
    stream >> mTryNumber;
    stream >> mMaxTries;
    stream >> mUserInfo;

    mStatus = ( HbNetworkProtocol::AuthStatus ) status;

    return true;
}

bool HbAuthStatusContract::write( QDataStream & stream ) const
{
    stream << ( netwint ) mStatus;
    stream << mDescription;
    stream << mTryNumber;
    stream << mMaxTries;
    stream << mUserInfo;

    return true;
}

void HbAuthStatusContract::setStatus( HbNetworkProtocol::AuthStatus status )
{
    mStatus = status;
}

void HbAuthStatusContract::setDescription( const QString & description )
{
    mDescription = description;
}

void HbAuthStatusContract::setTryNumber( quint8 try_number )
{
    mTryNumber = try_number;
}

void HbAuthStatusContract::setMaxTries ( quint8 max_tries )
{
    mMaxTries = max_tries;
}

void HbAuthStatusContract::setUserInfo( const HbNetworkUserInfo & user_info )
{
    mUserInfo = user_info;
}

HbNetworkProtocol::AuthStatus HbAuthStatusContract::status() const
{
    return mStatus;
}

const QString & HbAuthStatusContract::description() const
{
    return mDescription;
}

quint8 HbAuthStatusContract::tryNumber() const
{
    return mTryNumber;
}

quint8 HbAuthStatusContract::maxTries() const
{
    return mMaxTries;
}

const HbNetworkUserInfo & HbAuthStatusContract::userInfo() const
{
    return mUserInfo;
}
