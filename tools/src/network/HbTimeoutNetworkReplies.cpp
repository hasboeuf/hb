// Local
#include <network/HbTimeoutNetworkReplies.h>

using namespace hb::tools;

HbTimeoutNetworkReplies::~HbTimeoutNetworkReplies()
{
    qDeleteAll( mReplies );
    mReplies.clear();
}

qint64 HbTimeoutNetworkReplies::add( QNetworkReply * reply, quint32 timeout )
{
    if( reply )
    {
        HbTimeoutNetworkReply * timeout_reply = new HbTimeoutNetworkReply( reply, timeout, this );

        connect( timeout_reply, &QObject::destroyed, this, &HbTimeoutNetworkReplies::onDestroyed );

        mReplies.insert( reply, timeout_reply );

        return timeout_reply->id();
    }

    return -1;
}

void HbTimeoutNetworkReplies::remove( QNetworkReply * reply )
{
    if( !reply )
    {
        return;
    }

    mReplies.remove( reply );
}

qint64 HbTimeoutNetworkReplies::id( QNetworkReply * reply ) const
{
    if( reply )
    {
        HbTimeoutNetworkReply * timeout_reply = mReplies.value( reply, nullptr );
        if( timeout_reply )
        {
            return timeout_reply->id();
        }
    }

    return -1;
}

void HbTimeoutNetworkReplies::onDestroyed()
{
    QObject * object = sender();
    mReplies.remove( mReplies.key( static_cast< HbTimeoutNetworkReply * >( object ) ) );
}
