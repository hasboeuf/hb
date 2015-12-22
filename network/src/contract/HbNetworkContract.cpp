// Hb
#include <HbLogService.h>
// Local
#include <contract/HbNetworkContract.h>

using namespace hb::network;

HbNetworkContract::HbNetworkContract()
{
    mSender          = 0;
    mNetworkReceiver = 0;
    mNetworkType     = HbNetworkProtocol::NETWORK_UNDEFINED;
    mRouting         = HbNetworkProtocol::ROUTING_UNDEFINED;
    mpReply          = nullptr;
}

HbNetworkContract::HbNetworkContract( serviceuid service, codeuid code ) :
    mHeader( service, code )
{
    mSender      = 0;
    mNetworkType = HbNetworkProtocol::NETWORK_UNDEFINED;
    mRouting     = HbNetworkProtocol::ROUTING_UNDEFINED;
    mpReply      = nullptr;
}

HbNetworkContract::HbNetworkContract( const HbNetworkContract & source )
{
    if( &source != this )
    {
        mHeader           = source.mHeader;
        mSender           = source.mSender;
        mNetworkType      = source.mNetworkType;
        mRouting          = source.mRouting;
        mReceivers   = source.mReceivers;
        mPendingReceivers     = source.mPendingReceivers;
        mpReply           = ( source.mpReply ? source.mpReply->create() : nullptr );
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
        mReceivers        = source.mReceivers;
        mPendingReceivers = source.mPendingReceivers;
        mpReply           = ( source.mpReply ? source.mpReply->create() : nullptr );
    }
    return ( *this );
}

HbNetworkContract::~HbNetworkContract()
{
    if( mpReply ) delete mpReply;
}

void HbNetworkContract::updateReply()
{
    if( mpReply )
    {
        mpReply->takeUid( this );
        mpReply->setNetworkType( mNetworkType );
        mpReply->setRouting( HbNetworkProtocol::ROUTING_UNICAST ); // Replies only support unicast.
        mpReply->addSocketReceiver( mSender );
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

void HbNetworkContract::setSender( networkuid sender )
{
    mSender = sender;
}

networkuid HbNetworkContract::sender() const
{
    return mSender;
}

void HbNetworkContract::addPendingReceiver( ShConstHbNetworkUserInfo user_info )
{
    mPendingReceivers.push_back( user_info );
}

void HbNetworkContract::addSocketReceiver( networkuid socket_uid )
{
    mReceivers.insert( socket_uid );
}

void HbNetworkContract::resetReceivers()
{
    mReceivers.clear();
}

const QList< ShConstHbNetworkUserInfo > & HbNetworkContract::pendingReceivers() const
{
    return mPendingReceivers;
}

const QSet< networkuid > & HbNetworkContract::receivers() const
{
    return mReceivers;
}

networkuid HbNetworkContract::receiver() const
{
    if( mReceivers.size() == 1 )
    {
        return *mReceivers.begin();
    }
    return 0; // 0 is an invalid netwuid.
}

void HbNetworkContract::setNetworkReceiver( networkuid network_receiver )
{
    mNetworkReceiver = network_receiver;
}

networkuid HbNetworkContract::networkReceiver() const
{
    return mNetworkReceiver;
}

bool HbNetworkContract::isValid() const
{
    if( mRouting == HbNetworkProtocol::ROUTING_UNDEFINED )
    {
        HbError( "Routing is not defined." );
        return false;
    }

    if( mRouting == HbNetworkProtocol::ROUTING_UNICAST )
    {
        if ( mReceivers.size() != 1 )
        {
            HbError( "Only one receiver is allowed with unicast mode." );
            return false;
        }
    }
    else if( mRouting == HbNetworkProtocol::ROUTING_MULTICAST )
    {
        if( mReceivers.isEmpty() )
        {
            HbError( "No receivers set in multicast mode." );
            return false;
        }
        return true;
    }
    else // ROUTING_BROADCAST
    {
        if( mReceivers.size() > 0 )
        {
            HbWarning( "Receivers set in broadcast mode are ignored." );
        }
    }

    return true;
}

HbNetworkProtocol::RoutingScheme HbNetworkContract::routing() const
{
    return mRouting;
}

bool HbNetworkContract::setRouting( HbNetworkProtocol::RoutingScheme routing )
{
    if( mRouting == HbNetworkProtocol::ROUTING_UNDEFINED )
    {
        mRouting = routing;
        return true;
    }

    // HbWarning( "Routing is already set." );
    return false;
}

HbNetworkContract * HbNetworkContract::reply() const
{
    return mpReply;
}

const QString HbNetworkContract::toString() const
{
    return QString("ctctuid=%1,type=%2,%3")
            .arg( mUid )
            .arg( HbNetworkProtocol::MetaNetworkType::toString( mNetworkType ) )
            .arg( mHeader.toString() );
}

void HbNetworkContract::setNetworkType( HbNetworkProtocol::NetworkType type )
{
    mNetworkType = type;
}

HbNetworkProtocol::NetworkType HbNetworkContract::networkType() const
{
    return mNetworkType;
}
