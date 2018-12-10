#ifndef HBAUTH2REPLYHANDLER_H
#define HBAUTH2REPLYHANDLER_H

// Qt
#include <QtNetworkAuth/QOAuthHttpServerReplyHandler>

namespace hb {
namespace auth {

class HbAuth2ReplyHandler : public QOAuthOobReplyHandler {
public:
    HbAuth2ReplyHandler(QObject* parent = nullptr);

    using QOAuthOobReplyHandler::networkReplyFinished;

    QString callback() const override;

    virtual void init();
    virtual bool isReady() const;

    void setRedirectUrl(const QUrl& redirectUrl);
    QUrl redirectUrl() const;

    quint16 port() const;
    bool isSecure() const;

private:
    QUrl mRedirectUrl;
};
} // namespace auth
} // namespace hb

#endif // HBAUTH2REPLYHANDLER_H
