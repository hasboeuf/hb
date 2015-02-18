// Hb
#include <HbLogService.h>
// Local
#include <contract/HbNetworkContract.h>

using namespace hb::network;

HbNetworkContract::HbNetworkContract()
{
    mSender = 0;
    mNetworkType = HbNetworkProtocol::NETWORK_UNDEFINED;
    mRouting = HbNetworkProtocol::RoutingScheme::UNICAST;
    mpReply  = nullptr;
}

HbNetworkContract::HbNetworkContract( HbNetworkProtocol::Service service, HbNetworkProtocol::Code code ) :
    mHeader( service, code )
{
    mSender = 0;
    mNetworkType = HbNetworkProtocol::NETWORK_UNDEFINED;
    mRouting = HbNetworkProtocol::RoutingScheme::UNICAST;
    mpReply  = nullptr;
}

HbNetworkContract::HbNetworkContract( const HbNetworkContract & source )
{
    if( &source != this )
    {
        mHeader           = source.mHeader;
        mSender           = source.mSender;
        mNetworkType      = source.mNetworkType;
        mRouting          = source.mRouting;
        mPendingReceivers = source.mPendingReceivers;
        mSocketReceivers  = source.mSocketReceivers;
        mpReply           = nullptr; // TODO CHECK
    }
}

HbNetworkContract & HbNetworkContract::operator=( const HbNetworkContract & source )
{
    if( &source != this )
    {
        mHeader           = source.mHeader;
        mSender           = source.mSender;
        mNetworkType      = source.mNetworkType;
        mRouting          = source.mRouting;
        mPendingReceivers = source.mPendingReceivers;
        mSocketReceivers  = source.mSocketReceivers;
        mpReply           = nullptr; // TODO CHECK
    }
    return ( *this );
}

void HbNetworkContract::setReply( HbNetworkContract * reply )
{
    if( reply )
    {
        mpReply = reply;
        mpReply->takeUid( this );
        mpReply->resetSocketReceivers();
        mpReply->setNetworkType( mNetworkType );
        mpReply->setRouting( HbNetworkProtocol::RoutingScheme::UNICAST ); // Replies only support unicast.
        mpReply->addSocketReceiver( mUid );
    }
}

void HbNetworkContract::setHeader( const HbNetworkHeader & header )
{
    mHeader = header;
}

const HbNetworkHeader & HbNetworkContract::header() const
{
    return mHeader;
}

void HbNetworkContract::setSender( sockuid sender )
{
    mSender = sender;
}

sockuid HbNetworkContract::sender() const
{
    return mSender;
}

void HbNetworkContract::addPendingReceiver( const QString & user_uid )
{
    mPendingReceivers.insert( user_uid );
}

bool HbNetworkContract::addSocketReceiver( sockuid receiver )
{
    if( mRouting == HbNetworkProtocol::RoutingScheme::UNICAST )
    {
        if ( !mSocketReceivers.isEmpty() )
        {
            HbWarning( "A receiver is already defined in unicast mode." );
            return false;
        }

        mSocketReceivers.insert( receiver );
        return true;
    }
    else if( mRouting == HbNetworkProtocol::RoutingScheme::MULTICAST )
    {
        mSocketReceivers.insert( receiver );
        return true;
    }
    else
    {
        HbWarning( "Unable to add a receiver in broadcast mode." );
        return false;
    }
}

void HbNetworkContract::resetSocketReceivers()
{
    mSocketReceivers.clear();
}

const QSet< sockuid > & HbNetworkContract::socketReceivers() const
{
    return mSocketReceivers;
}

sockuid HbNetworkContract::socketReceiver() const
{
    if( mSocketReceivers.size() > 0 )
    {
        return *mSocketReceivers.begin();
    }
    return 0; // 0 is an invalid sockuid.
}

HbNetworkProtocol::RoutingScheme HbNetworkContract::routing() const
{
    return mRouting;
}

void HbNetworkContract::setRouting( HbNetworkProtocol::RoutingScheme routing )
{
    mRouting = routing;
    // TODO logique routing.
}

HbNetworkContract * HbNetworkContract::reply() const
{
    return mpReply;
}

void HbNetworkContract::setNetworkType( HbNetworkProtocol::NetworkType type )
{
    mNetworkType = type;
}

HbNetworkProtocol::NetworkType HbNetworkContract::networkType() const
{
    return mNetworkType;
}
