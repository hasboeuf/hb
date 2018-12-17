// Local
#include <network/HbTimeoutNetworkReplies.h>

using namespace hb::tools;

HbTimeoutNetworkReplies::HbTimeoutNetworkReplies(QObject* parent) : QObject(parent) {
}

HbTimeoutNetworkReplies::~HbTimeoutNetworkReplies() {
    printf("~HbTimeoutNetworkReplies mReplies=%d\n", mReplies.size());

    for (QNetworkReply* reply : mReplies.keys()) {
        delete reply;
    }
    mReplies.clear();
}

quint64 HbTimeoutNetworkReplies::add(QNetworkReply* reply, quint32 timeout) {
    if (reply) {
        HbTimeoutNetworkReply* timeout_reply = new HbTimeoutNetworkReply(reply, timeout);

        // connect( reply, &QNetworkReply::finished, this, &HbTimeoutNetworkReplies::onFinished );

        mReplies.insert(reply, timeout_reply->uid());

        return timeout_reply->uid();
    }

    return 0;
}

void HbTimeoutNetworkReplies::remove(QNetworkReply* reply) {
    if (!reply) {
        return;
    }

    reply->close(); // onFinished will handle the rest.
}

quint64 HbTimeoutNetworkReplies::id(QNetworkReply* reply) const {
    return mReplies.value(reply, 0);
}

void HbTimeoutNetworkReplies::onFinished() {
    QNetworkReply* reply = dynamic_cast<QNetworkReply*>(sender());
    if (!reply) {
        return;
    }

    mReplies.remove(reply);
}
