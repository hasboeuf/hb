// Local
#include <network/HbTimeoutNetworkReplies.h>

using namespace hb::tools;

HbTimeoutNetworkReplies::~HbTimeoutNetworkReplies()
{
    printf( "~HbTimeoutNetworkReplies mReplies=%d\n", mReplies.size() );
    qDeleteAll( mReplies );
    mReplies.clear();
}

quint64 HbTimeoutNetworkReplies::add( QNetworkReply * reply, quint32 timeout )
{
    if( reply )
    {
        HbTimeoutNetworkReply * timeout_reply = new HbTimeoutNetworkReply( reply, timeout, this );

        connect( timeout_reply, &QObject::destroyed, this, &HbTimeoutNetworkReplies::onDestroyed, Qt::UniqueConnection );

        mReplies.insert( reply, timeout_reply );

        return timeout_reply->uid();
    }

    return 0;
}

void HbTimeoutNetworkReplies::remove( QNetworkReply * reply )
{
    if( !reply )
    {
        return;
    }

    mReplies.remove( reply );
}

quint64 HbTimeoutNetworkReplies::id( QNetworkReply * reply ) const
{
    if( reply )
    {
        HbTimeoutNetworkReply * timeout_reply = mReplies.value( reply, nullptr );
        if( timeout_reply )
        {
            return timeout_reply->uid();
        }
    }

    return 0;
}

void HbTimeoutNetworkReplies::onDestroyed()
{
    QObject * object = sender();
    printf( "onDestroyed before mReplies=%d\n", mReplies.size() );
    mReplies.remove( mReplies.key( static_cast< HbTimeoutNetworkReply * >( object ) ) );
    printf( "onDestroyed after mReplies=%d\n", mReplies.size() );
}
