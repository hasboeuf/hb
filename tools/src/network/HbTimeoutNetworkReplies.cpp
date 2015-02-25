// Local
#include <network/HbTimeoutNetworkReplies.h>

using namespace hb::tools;

HbTimeoutNetworkReplies::~HbTimeoutNetworkReplies()
{
    printf( "~HbTimeoutNetworkReplies mReplies=%d\n", mReplies.size() );
    auto it = mReplies.begin();
    while( it != mReplies.end() )
    {
        QNetworkReply * reply                 = it.key();
        HbTimeoutNetworkReply * timeout_reply = it.value();

        if( reply ) delete reply;
        if( timeout_reply ) delete timeout_reply;

        ++it;
    }
}

quint64 HbTimeoutNetworkReplies::add( QNetworkReply * reply, quint32 timeout )
{
    if( reply )
    {
        HbTimeoutNetworkReply * timeout_reply = new HbTimeoutNetworkReply( reply, timeout, this );

        connect( reply, &QNetworkReply::finished, this, &HbTimeoutNetworkReplies::onFinished );

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

    reply->close(); // onFinished will handle the rest.
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

void HbTimeoutNetworkReplies::onFinished()
{
    QNetworkReply * reply = dynamic_cast< QNetworkReply * >( sender() );
    if( !reply )
    {
        return;
    }

    HbTimeoutNetworkReply * timeout_reply = mReplies.value( reply, nullptr );
    if( timeout_reply )
    {
        mReplies.remove( reply);
        delete timeout_reply;
    }
}
