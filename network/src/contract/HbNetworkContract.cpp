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
        mpReply->addReceiver( mUid );
        mpReply->setNetworkType( mNetworkType );
        mpReply->setRouting( HbNetworkProtocol::RoutingScheme::UNICAST ); // Replies only support unicast.
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

bool HbNetworkContract::addReceiver( sockuid receiver )
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

void HbNetworkContract::resetReceivers()
{
    mSocketReceivers.clear();
}

const QSet< sockuid > & HbNetworkContract::receivers() const
{
    return mSocketReceivers;
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
