// Local
#include <HbGlobal.h>
#include <network/HbTimeoutNetworkReply.h>

using namespace hb::tools;

quint32 HbTimeoutNetworkReply::msDefaultTimeout = 1000 * 60;

HbTimeoutNetworkReply::HbTimeoutNetworkReply(QNetworkReply* reply, quint32 timeout) : QTimer(reply) {
    setSingleShot(true);

    q_assert_ptr(reply);

    connect(this,
            &HbTimeoutNetworkReply::error,
            reply,
            (void (QNetworkReply::*)(QNetworkReply::NetworkError))(&QNetworkReply::error),
            Qt::UniqueConnection);
    connect(this, &QTimer::timeout, this, &HbTimeoutNetworkReply::onTimeout, Qt::UniqueConnection);

    if (timeout < 100) {
        timeout = 100;
    }
    start(timeout);
}

HbTimeoutNetworkReply::~HbTimeoutNetworkReply() {
    printf("~HbTimeoutNetworkReply\n");
}

void HbTimeoutNetworkReply::onTimeout() {
    // emit error( QNetworkReply::TimeoutError );
}
