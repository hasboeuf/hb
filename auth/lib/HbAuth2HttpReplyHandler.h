#ifndef HBAUTH2HTTPREPLYHANDLER_H
#define HBAUTH2HTTPREPLYHANDLER_H

// Local
#include <HbAuth2ReplyHandler.h>

class QTcpSocket;

namespace hb {
namespace auth {

class HbAuthHttpServer;
class HbAuth2HttpReplyHandler : public HbAuth2ReplyHandler {
public:
    HbAuth2HttpReplyHandler(QObject* parent = nullptr);

    void init() override;
    bool isReady() const override;

private:
    struct HttpRequest {
        quint16 port = 0;

        bool readMethod(QTcpSocket* socket);
        bool readUrl(QTcpSocket* socket);
        bool readStatus(QTcpSocket* socket);
        bool readHeader(QTcpSocket* socket);

        enum class State {
            ReadingMethod,
            ReadingUrl,
            ReadingStatus,
            ReadingHeader,
            ReadingBody,
            AllDone
        } state = State::ReadingMethod;
        QByteArray fragment;

        enum class Method {
            Unknown,
            Head,
            Get,
            Put,
            Post,
            Delete,
        } method = Method::Unknown;
        QUrl url;
        QPair<quint8, quint8> version;
        QMap<QByteArray, QByteArray> headers;
    };

    void onSocketConnected(QTcpSocket* socket);
    void readData(QTcpSocket* socket);
    void answerClient(QTcpSocket* socket, const QUrl& url);
    HbAuthHttpServer* mHttpServer = nullptr;
    QHash<QTcpSocket*, HttpRequest> mClients;
};

} // namespace auth
} // namespace hb

#endif // HBAUTH2HTTPREPLYHANDLER_H
