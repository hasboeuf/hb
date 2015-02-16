// Hb
#include <core/HbUuidGenerator.h>
// Local
#include <HbGlobal.h>
#include <network/HbTimeoutNetworkReply.h>

using namespace hb::tools;

quint32 HbTimeoutNetworkReply::msDefaultTimeout = 1000 * 60;

HbTimeoutNetworkReply::HbTimeoutNetworkReply( QNetworkReply * reply, quint32 timeout, QObject * parent ) :
    QTimer( parent )
{
    setSingleShot( true );

    q_assert_ptr( reply );

    mId = HbUuidGenerator< replyuuid, CLASS_REPLIES >::get()->uuid( true );

    connect( this, &HbTimeoutNetworkReply::error,
             reply, ( void (QNetworkReply::*)( QNetworkReply::NetworkError ) )( &QNetworkReply::error ) );
    connect( this, &QTimer::timeout, this, &HbTimeoutNetworkReply::onTimeout );
    connect( reply, &QObject::destroyed, this, &QObject::deleteLater );

    if( timeout < 100 )
    {
        timeout = 100;
    }
    start( timeout );
}

HbTimeoutNetworkReply::~HbTimeoutNetworkReply()
{
    HbUuidGenerator< replyuuid, CLASS_REPLIES >::get()->releaseUuid( mId );
}

quint64 HbTimeoutNetworkReply::id() const
{
    return mId;
}

void HbTimeoutNetworkReply::onTimeout()
{
    emit error( QNetworkReply::TimeoutError );
}


