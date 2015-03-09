// Local
#include <contract/general/HbKickContract.h>

using namespace hb::network;

HbKickContract::HbKickContract() :
    HbNetworkContract( HbNetworkProtocol::SERVICE_KICK,
                       HbNetworkProtocol::CODE_SRV_KICK )
{
    setRouting( HbNetworkProtocol::ROUTING_UNICAST );
    mReason    = HbNetworkProtocol::KICK_UNDEFINED;
}

HbKickContract::HbKickContract( const HbKickContract & source ) :
    HbNetworkContract( source )
{
    if( & source != this )
    {
        mReason      = source.mReason;
        mDescription = source.mDescription;
    }
}

HbKickContract & HbKickContract::operator=( const HbKickContract & source )
{
    if( &source != this )
    {
        HbNetworkContract::operator=( source );

        mReason      = source.mReason;
        mDescription = source.mDescription;
    }

    return ( *this );
}

HbKickContract * HbKickContract::create() const
{
    return new HbKickContract();
}

bool HbKickContract::read( QDataStream & stream )
{
    stream >> mReason;
    stream >> mDescription;

    return true;
}

bool HbKickContract::write( QDataStream & stream ) const
{
    stream << mReason;
    stream << mDescription;

    return true;
}

void HbKickContract::setReason( netwint reason )
{
    mReason = reason;
}

void HbKickContract::setDescription( const QString & description )
{
    mDescription = description;
}

netwint HbKickContract::reason() const
{
    return mReason;
}

const QString & HbKickContract::description() const
{
    return mDescription;
}
