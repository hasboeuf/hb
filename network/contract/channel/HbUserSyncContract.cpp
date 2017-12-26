// Local
#include <contract/channel/HbUserSyncContract.h>
#include <contract/HbNetworkProtocol.h>

HbUserSyncContract::HbUserSyncContract() :
    HbNetworkContract( HbNetworkProtocol::SERVICE_CHANNEL,
                       HbNetworkProtocol::CODE_SRV_USER_CONNECTED )
{
    setRouting( HbNetworkProtocol::ROUTING_MULTICAST );
}

HbUserSyncContract::HbUserSyncContract( const HbUserSyncContract & source ) :
    HbNetworkContract( source )
{
    if( & source != this )
    {
        mSyncs = source.mSyncs;
    }
}

HbUserSyncContract & HbUserSyncContract::operator=( const HbUserSyncContract & source )
{
    if( &source != this )
    {
        HbNetworkContract::operator=( source );

        mSyncs = source.mSyncs;
    }

    return ( *this );
}

HbUserSyncContract * HbUserSyncContract::create() const
{
    return new HbUserSyncContract();
}

void HbUserSyncContract::addSync( const HbNetworkUserSync & user_sync )
{
    mSyncs.push_back( user_sync );
}

const QList< hb::network::HbNetworkUserSync > & HbUserSyncContract::syncs() const
{
    return mSyncs;
}

bool HbUserSyncContract::read( QDataStream & stream )
{
    stream >> mSyncs;

    return true;
}

bool HbUserSyncContract::write( QDataStream & stream ) const
{
    stream << mSyncs;

    return true;
}
