// Hb
#include <HbLogService.h>
// Local
#include <contract/HbComContract.h>

using namespace hb::com;

HbComContract::HbComContract()
{
    mSender = 0;
    mComType = HbComProtocol::COM_UNDEFINED;
    mRouting = HbComProtocol::RoutingScheme::UNICAST;
    mpReply  = nullptr;
}

HbComContract::HbComContract( servuid service, codeuid code ) :
    mHeader( service, code )
{
    mSender = 0;
    mComType = HbComProtocol::COM_UNDEFINED;
    mRouting = HbComProtocol::RoutingScheme::UNICAST;
    mpReply  = nullptr;
}

HbComContract::HbComContract( const HbComContract & source )
{
    if( &source != this )
    {
        mHeader           = source.mHeader;
        mSender           = source.mSender;
        mComType      = source.mComType;
        mRouting          = source.mRouting;
        mPendingReceivers = source.mPendingReceivers;
        mSocketReceivers  = source.mSocketReceivers;
        mpReply           = nullptr; // TODO CHECK
    }
}

HbComContract & HbComContract::operator=( const HbComContract & source )
{
    if( &source != this )
    {
        mHeader           = source.mHeader;
        mSender           = source.mSender;
        mComType      = source.mComType;
        mRouting          = source.mRouting;
        mPendingReceivers = source.mPendingReceivers;
        mSocketReceivers  = source.mSocketReceivers;
        mpReply           = nullptr; // TODO CHECK
    }
    return ( *this );
}

void HbComContract::setReply( HbComContract * reply )
{
    if( reply )
    {
        mpReply = reply;
        mpReply->takeUid( this );
        mpReply->resetSocketReceivers();
        mpReply->setComType( mComType );
        mpReply->setRouting( HbComProtocol::RoutingScheme::UNICAST ); // Replies only support unicast.
        mpReply->addSocketReceiver( mUid );
    }
}

void HbComContract::setHeader( const HbComHeader & header )
{
    mHeader = header;
}

const HbComHeader & HbComContract::header() const
{
    return mHeader;
}

void HbComContract::setSender( sockuid sender )
{
    mSender = sender;
}

sockuid HbComContract::sender() const
{
    return mSender;
}

void HbComContract::addPendingReceiver( const QString & user_uid )
{
    mPendingReceivers.insert( user_uid );
}

bool HbComContract::addSocketReceiver( sockuid receiver )
{
    if( mRouting == HbComProtocol::RoutingScheme::UNICAST )
    {
        if ( !mSocketReceivers.isEmpty() )
        {
            HbWarning( "A receiver is already defined in unicast mode." );
            return false;
        }

        mSocketReceivers.insert( receiver );
        return true;
    }
    else if( mRouting == HbComProtocol::RoutingScheme::MULTICAST )
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

void HbComContract::resetSocketReceivers()
{
    mSocketReceivers.clear();
}

const QSet< sockuid > & HbComContract::socketReceivers() const
{
    return mSocketReceivers;
}

sockuid HbComContract::socketReceiver() const
{
    if( mSocketReceivers.size() > 0 )
    {
        return *mSocketReceivers.begin();
    }
    return 0; // 0 is an invalid sockuid.
}

HbComProtocol::RoutingScheme HbComContract::routing() const
{
    return mRouting;
}

void HbComContract::setRouting( HbComProtocol::RoutingScheme routing )
{
    mRouting = routing;
    // TODO logique routing.
}

HbComContract * HbComContract::reply() const
{
    return mpReply;
}

void HbComContract::setComType( HbComProtocol::ComType type )
{
    mComType = type;
}

HbComProtocol::ComType HbComContract::networkType() const
{
    return mComType;
}
