// Hb
#include <HbLogService.h>
// Local
#include <contract/HbNetworkContract.h>

using namespace hb::network;

HbNetworkContract::HbNetworkContract( HbNetworkProtocol::Service service, HbNetworkProtocol::Code code ) :
    mHeader( service, code )
{
    mNetworkTarget = HbNetworkProtocol::NETWORK_UNDEFINED;
    mRouting = HbNetworkProtocol::RoutingScheme::UNICAST;
    mpReply  = nullptr;
}

HbNetworkContract::HbNetworkContract( const HbNetworkContract & source )
{
    if( &source != this )
    {
        mHeader           = source.mHeader;
        mNetworkTarget    = source.mNetworkTarget;
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
        mNetworkTarget    = source.mNetworkTarget;
        mRouting          = source.mRouting;
        mPendingReceivers = source.mPendingReceivers;
        mSocketReceivers  = source.mSocketReceivers;
        mpReply           = nullptr; // TODO CHECK
    }
    return ( *this );
}

void HbNetworkContract::setHeader( const HbNetworkHeader & header )
{
    mHeader = header;
}

const HbNetworkHeader & HbNetworkContract::header() const
{
    return mHeader;
}

void HbNetworkContract::addPendingReceiver( const QString & user_uuid )
{
    mPendingReceivers.insert( user_uuid );
}

bool HbNetworkContract::addReceiver( quint16 receiver )
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

const QSet< quint16 > & HbNetworkContract::receivers() const
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


bool HbNetworkContract::setReply( HbNetworkContract * reply )
{
    if ( reply && ( mpReply != reply ) )
	{
        if ( mRouting != HbNetworkProtocol::RoutingScheme::UNICAST )
		{
            HbWarning( "Reply only supported in unicast mode." );
			return false;
		}

        mpReply = reply;
	}

	return true;
}

HbNetworkContract * HbNetworkContract::reply() const
{
    return mpReply;
}
