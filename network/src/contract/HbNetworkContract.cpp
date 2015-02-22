// Hb
#include <HbLogService.h>
// Local
#include <contract/HbNetworkContract.h>

using namespace hb::network;

HbNetworkContract::HbNetworkContract()
{
    mSender      = 0;
    mNetworkType = HbNetworkProtocol::NETWORK_UNDEFINED;
    mRouting     = HbNetworkProtocol::RoutingScheme::UNICAST;
    mpReply      = nullptr;
}

HbNetworkContract::~HbNetworkContract()
{
    //HbDebug( "HbNetworkContract::destructor()" );
}

HbNetworkContract::HbNetworkContract( serviceuid service, codeuid code ) :
    mHeader( service, code )
{
    mSender      = 0;
    mNetworkType = HbNetworkProtocol::NETWORK_UNDEFINED;
    mRouting     = HbNetworkProtocol::RoutingScheme::UNICAST;
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

void HbNetworkContract::updateReply()
{
    if( mpReply )
    {
        mpReply->takeUid( this );
        mpReply->resetSocketReceivers();
        mpReply->setNetworkType( mNetworkType );
        mpReply->setRouting( HbNetworkProtocol::RoutingScheme::UNICAST ); // Replies only support unicast.
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

void HbNetworkContract::addPendingReceiver( const QString & user_uid )
{
    mPendingReceivers.insert( user_uid );
}

bool HbNetworkContract::addSocketReceiver( networkuid receiver )
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

const QSet< networkuid > & HbNetworkContract::socketReceivers() const
{
    return mSocketReceivers;
}

networkuid HbNetworkContract::socketReceiver() const
{
    if( mSocketReceivers.size() == 1 )
    {
        return *mSocketReceivers.begin();
    }
    return 0; // 0 is an invalid netwuid.
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
