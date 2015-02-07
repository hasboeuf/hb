// Local
#include <network/HbTimeoutNetworkReplies.h>

using namespace hb::tools;

HbTimeoutNetworkReplies::~HbTimeoutNetworkReplies()
{
    qDeleteAll( mReplies );
    mReplies.clear();
}

void HbTimeoutNetworkReplies::add( QNetworkReply * reply, quint32 timeout )
{
    if( reply )
    {
        HbTimeoutNetworkReply * timeout_reply = new HbTimeoutNetworkReply( reply, timeout, this );
        add( timeout_reply );
    }
}

void HbTimeoutNetworkReplies::add( HbTimeoutNetworkReply * timeout_reply )
{
    if( !timeout_reply )
    {
        return;
    }

    connect( timeout_reply, &QObject::destroyed, this, &HbTimeoutNetworkReplies::onDestroyed );

    mReplies.append( timeout_reply );
}

void HbTimeoutNetworkReplies::onDestroyed()
{
    QObject * object = sender();
    mReplies.removeOne( static_cast< HbTimeoutNetworkReply * >( object ) );
}
