// Qt
#include <QtCore/QPair>
#include <QtCore/QUrlQuery>
// Hb
#include <HbLogService.h>
#include <core/HbDictionaryHelper.h>
// Local
#include <HbO2Client.h>
#include <IHbLinkBrowserControls.h>

using namespace hb::link;

bool HbO2Client::isValid() const {
    if (!HbO2::isValid()) {
        return false;
    }

    return mConfig.isValid();
}

HbO2ClientConfig& HbO2Client::config() {
    return mConfig;
}

const HbO2ClientConfig& HbO2Client::config() const {
    return mConfig;
}

bool HbO2Client::link() {
    mRedirectUri = REDIRECT_URI.arg(mConfig.localPort()); // Complete uri with the port.

    if (!isValid()) {
        qWarning() << "O2Client config invalid";
        return false;
    }

    connect(this, &HbO2Client::openBrowser, mConfig.browserControls(), &IHbLinkBrowserControls::onOpenBrowser);
    connect(this, &HbO2Client::closeBrowser, mConfig.browserControls(), &IHbLinkBrowserControls::onCloseBrowser);

    mLinkStatus = LINKING;

    if (mReplyServer.isListening()) {
        mReplyServer.close();
    }

    mReplyServer.listen(QHostAddress::Any, mConfig.localPort());
    connect(&mReplyServer,
            &HbLinkLocalServer::responseReceived,
            this,
            &HbO2Client::onCodeResponseReceived,
            Qt::UniqueConnection);

    QUrl url(endPoint());

    QUrlQuery request(url);
    request.setQueryItems(HbDictionaryHelper::toPairList<QString, QString>(codeRequest()));
    url.setQuery(request);

    qDebug() << "Url to open:" << url.toString();

    emit openBrowser(url);

    return true;
}

void HbO2Client::onCodeResponseReceived(const QHash<QString, QString> response) {
    if (codeResponse(response) == LINKED) {
        qDebug() << "Verification succeed";
        qDebug() << "Code received:" << mCode;
        mLinkStatus = LINKED;
        emit linkSucceed();
    } else {
        qWarning() << "Verification failed" << mErrorString;
        mLinkStatus = UNLINKED;
        emit linkFailed(mErrorString);
    }

    emit closeBrowser();
}
