// Hb
#include <HbLogService.h>
// Local
#include <contract/HbNetworkContract.h>

using namespace hb::network;

HbNetworkContract::HbNetworkContract( HbNetworkProtocol::Service service, HbNetworkProtocol::Code code) :
    mHeader( service, code )
{
    mNetworkTarget = HbNetworkProtocol::NETWORK_UNDEFINED;
    mpReply  = nullptr;
}

HbNetworkContract::HbNetworkContract( const HbNetworkContract & source )
{
    if( &source != this )
    {
        mHeader           = source.mHeader;
        mNetworkTarget    = source.mNetworkTarget;
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
        mPendingReceivers = source.mPendingReceivers;
        mSocketReceivers  = source.mSocketReceivers;
        mpReply           = nullptr; // TODO CHECK
    }
    return ( *this );
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
    if( mHeader.routing() == HbNetworkProtocol::RoutingScheme::UNICAST )
    {
        if ( !mSocketReceivers.isEmpty() )
        {
            HbWarning( "A receiver is already defined in unicast mode." );
            return false;
        }

        mSocketReceivers.insert( receiver );
        return true;
    }
    else if( mHeader.routing() == HbNetworkProtocol::RoutingScheme::MULTICAST )
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


bool HbNetworkContract::setReply( HbNetworkContract * reply )
{
    if ( reply && ( mpReply != reply ) )
	{
        if ( mHeader.routing() != HbNetworkProtocol::RoutingScheme::UNICAST )
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
