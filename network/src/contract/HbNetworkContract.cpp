// Hb
#include <HbLogService.h>
// Local
#include <contract/HbNetworkContract.h>

using namespace hb::network;

HbNetworkContract::HbNetworkContract( HbNetworkProtocol::Service service, HbNetworkProtocol::Code code)
{
    mService = service;
    mCode    = code;
    mRouting = HbNetworkProtocol::RoutingScheme::UNICAST;
    mpReply  = nullptr;
}

HbNetworkContract::HbNetworkContract( const HbNetworkContract & source )
{
    if( &source != this )
    {
        mService = source.mService;
        mCode    = source.mCode;
        mRouting = source.mRouting;
        mpReply  = source.mpReply; // TODO copy ptr.
    }
}

HbNetworkContract & HbNetworkContract::operator=( const HbNetworkContract & source )
{
    if( &source != this )
    {
        mService = source.mService;
        mCode    = source.mCode;
        mRouting = source.mRouting;
        mpReply  = source.mpReply; // TODO copy ptr.
    }
    return ( *this );
}

HbNetworkProtocol::Service HbNetworkContract::service() const
{
    return mService;
}

HbNetworkProtocol::Code HbNetworkContract::code() const
{
    return mCode;
}


void HbNetworkContract::setRouting( HbNetworkProtocol::RoutingScheme routing)
{
    if (mRouting != routing)
	{
        mRouting = routing;

        if ( mRouting == HbNetworkProtocol::RoutingScheme::BROADCAST )
		{
            if ( mReceivers.size() > 0)
            {
                HbWarning( "Predefined receivers will be cleared." );
            }
			
            mReceivers.clear();
		}

        if ( mRouting == HbNetworkProtocol::RoutingScheme::UNICAST )
        {
            if ( mReceivers.size() > 1 )
            {
                HbWarning( "Only the first receiver is kept." );

                int receiver = *mReceivers.begin();

                mReceivers.clear();
                mReceivers.insert( receiver );
            }
        }
	}
}

HbNetworkProtocol::RoutingScheme HbNetworkContract::routing() const
{
    if( mRouting == HbNetworkProtocol::RoutingScheme::MULTICAST && mReceivers.isEmpty() )
    {
        return HbNetworkProtocol::RoutingScheme::BROADCAST;
    }

    return mRouting;
}


bool HbNetworkContract::addReceiver( quint16 receiver )
{
    if( mRouting == HbNetworkProtocol::RoutingScheme::UNICAST )
    {
        if ( !mReceivers.isEmpty() )
        {
            HbWarning( "A receiver is already defined in unicast mode." );
            return false;
        }

        mReceivers.insert( receiver );
        return true;
    }
    else if( mRouting == HbNetworkProtocol::RoutingScheme::MULTICAST )
    {
        mReceivers.insert( receiver );
        return true;
    }
    else
    {
        HbWarning( "Unable to add a receiver in broadcast mode." );
        return false;
    }
}

bool HbNetworkContract::setReceiver( quint16 receiver )
{
    resetReceivers();
    return addReceiver( receiver );
}

void HbNetworkContract::resetReceivers()
{
    mReceivers.clear();
}

const QSet< quint16 > & HbNetworkContract::receivers() const
{
    return mReceivers;
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
