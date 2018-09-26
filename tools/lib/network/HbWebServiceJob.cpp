// Qt
#include <QtCore/QTimer>
#include <QtNetwork/QNetworkAccessManager>
// Local
#include <network/HbWebServiceJob.h>

using namespace hb::tools;

HbWebServiceJob::HbWebServiceJob(QObject* parent) : QObject(parent) {
}

void HbWebServiceJob::cancel() {
    if (mCancelling) {
        return;
    }
    mCancelling = true;
    emit cancelRequested();
}

bool HbWebServiceJob::waitForFinished(int timeout) {
    if (!mCancelling) {
        if (timeout > -1) {
            QTimer::singleShot(timeout, this, [this]() { cancel(); });
        }
    }
    mEventLoop.exec();
    deleteLater();
    return !mCancelling;
}

HbWebServiceResult HbWebServiceJob::result() const {
    return mResult;
}

void HbWebServiceJob::setResult(const HbWebServiceResult& result) {
    mResult = result;
    emit finished(mResult);
    if (mEventLoop.isRunning()) {
        mEventLoop.quit();
        // deletion is handled in waitForFinished.
        return;
    }
    deleteLater();
}
