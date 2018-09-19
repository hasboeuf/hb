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
        mNetworkReceiver  = source.mNetworkReceiver;
        mNetworkType      = source.mNetworkType;
        mRouting          = source.mRouting;
        mReceivers        = source.mReceivers;
        mPendingReceivers = source.mPendingReceivers;
        mpReply           = ( source.mpReply ? source.mpReply->create() : nullptr );
    }
}

HbNetworkContract & HbNetworkContract::operator=( const HbNetworkContract & source )
{
    if( &source != this )
    {
        mHeader           = source.mHeader;
        mSender           = source.mSender;
        mNetworkReceiver  = source.mNetworkReceiver;
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
    if( mpReply )
    {
        // Delete reply if user did not take it.
        delete mpReply;
    }
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
        qWarning() << "Routing is not defined" << mHeader.toString();
        return false;
    }

    if( mRouting == HbNetworkProtocol::ROUTING_UNICAST )
    {
        if ( mReceivers.size() != 1 )
        {
            qWarning() << QString("Only one receiver (size=%1) is allowed with unicast mode (%2)")
                          .arg(mReceivers.size()).arg(mHeader.toString());
            return false;
        }
    }
    else if( mRouting == HbNetworkProtocol::ROUTING_MULTICAST )
    {
        if( mReceivers.isEmpty() )
        {
            qWarning() << "No receivers set in multicast mode" << mHeader.toString();
            return false;
        }
        return true;
    }
    else // ROUTING_BROADCAST
    {
        if( mReceivers.size() > 0 )
        {
            qWarning() << "Receivers set in broadcast mode are ignored" << mHeader.toString();
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

    return false;
}

HbNetworkContract * HbNetworkContract::takeReply() const
{
    if( !mpReply )
    {
        return nullptr;
    }

    HbNetworkContract * reply = mpReply;

    HbNetworkContract * this_non_const = const_cast< HbNetworkContract * >( this ); // Hack to avoid breaking const-correctness in the reception flow of HbNetwork.
    this_non_const->mpReply = nullptr;                                              // User takes reply, so it must be deleted by himself.

    return reply;
}

QString HbNetworkContract::toString() const
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
