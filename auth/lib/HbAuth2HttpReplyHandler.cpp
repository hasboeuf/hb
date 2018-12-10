// Qt
#include <QtCore/QCoreApplication>
#include <QtCore/QUrlQuery>
#include <QtNetwork/QSslSocket>
#include <QtNetwork/QTcpSocket>
// Local
#include <HbAuth2HttpReplyHandler.h>
#include <HbAuthHttpServer.h>

using namespace hb::auth;

bool HbAuth2HttpReplyHandler::HttpRequest::readMethod(QTcpSocket* socket) {
    bool finished = false;
    while (socket->bytesAvailable() && !finished) {
        const auto c = socket->read(1).at(0);
        if (std::isupper(c) && fragment.size() < 6)
            fragment += c;
        else
            finished = true;
    }
    if (finished) {
        if (fragment == "HEAD")
            method = Method::Head;
        else if (fragment == "GET")
            method = Method::Get;
        else if (fragment == "PUT")
            method = Method::Put;
        else if (fragment == "POST")
            method = Method::Post;
        else if (fragment == "DELETE")
            method = Method::Delete;
        else
            qWarning() << "Invalid operation" << fragment.data();

        state = State::ReadingUrl;
        fragment.clear();

        return method != Method::Unknown;
    }
    return true;
}

bool HbAuth2HttpReplyHandler::HttpRequest::readUrl(QTcpSocket* socket) {
    bool finished = false;
    while (socket->bytesAvailable() && !finished) {
        const auto c = socket->read(1).at(0);
        if (std::isspace(c))
            finished = true;
        else
            fragment += c;
    }
    if (finished) {
        if (!fragment.startsWith("/")) {
            qWarning() << "Invalid URL path" << fragment.constData();
            return false;
        }
        url.setUrl(QStringLiteral("http://localhost:") + QString::number(port) + QString::fromUtf8(fragment));
        state = State::ReadingStatus;
        if (!url.isValid()) {
            qWarning() << "Invalid URL" << fragment.constData();
            return false;
        }
        fragment.clear();
        return true;
    }
    return true;
}

bool HbAuth2HttpReplyHandler::HttpRequest::readStatus(QTcpSocket* socket) {
    bool finished = false;
    while (socket->bytesAvailable() && !finished) {
        fragment += socket->read(1);
        if (fragment.endsWith("\r\n")) {
            finished = true;
            fragment.resize(fragment.size() - 2);
        }
    }
    if (finished) {
        if (!std::isdigit(fragment.at(fragment.size() - 3)) || !std::isdigit(fragment.at(fragment.size() - 1))) {
            qWarning() << "Invalid version";
            return false;
        }
        version = qMakePair(fragment.at(fragment.size() - 3) - '0', fragment.at(fragment.size() - 1) - '0');
        state = State::ReadingHeader;
        fragment.clear();
    }
    return true;
}

bool HbAuth2HttpReplyHandler::HttpRequest::readHeader(QTcpSocket* socket) {
    while (socket->bytesAvailable()) {
        fragment += socket->read(1);
        if (fragment.endsWith("\r\n")) {
            if (fragment == "\r\n") {
                state = State::ReadingBody;
                fragment.clear();
                return true;
            } else {
                fragment.chop(2);
                const int index = fragment.indexOf(':');
                if (index == -1)
                    return false;

                const QByteArray key = fragment.mid(0, index).trimmed();
                const QByteArray value = fragment.mid(index + 1).trimmed();
                headers.insert(key, value);
                fragment.clear();
            }
        }
    }
    return false;
}

HbAuth2HttpReplyHandler::HbAuth2HttpReplyHandler(QObject* parent) : HbAuth2ReplyHandler(parent) {
}

void HbAuth2HttpReplyHandler::init() {
    mHttpServer = new HbAuthHttpServer(port(), isSecure(), this);
    QObject::connect(
        mHttpServer, &HbAuthHttpServer::socketConnected, this, &HbAuth2HttpReplyHandler::onSocketConnected);
    mHttpServer->listen(QHostAddress::LocalHost, port());
}

bool HbAuth2HttpReplyHandler::isReady() const {
    Q_ASSERT(mHttpServer);
    return mHttpServer->isListening();
}

void HbAuth2HttpReplyHandler::onSocketConnected(QTcpSocket* socket) {
    QObject::connect(socket, &QTcpSocket::disconnected, socket, &QTcpSocket::deleteLater);
    QObject::connect(socket, &QTcpSocket::readyRead, this, [this, socket]() { readData(socket); });
}

void HbAuth2HttpReplyHandler::readData(QTcpSocket* socket) {
    if (!mClients.contains(socket)) {
        mClients[socket].port = port();
    }

    HttpRequest* request = &mClients[socket];
    bool error = false;

    if (request->state == HttpRequest::State::ReadingMethod)
        if ((error = !request->readMethod(socket)))
            qWarning() << "Invalid Method";

    if (!error && request->state == HttpRequest::State::ReadingUrl)
        if ((error = !request->readUrl(socket)))
            qWarning() << "Invalid URL";

    if (!error && request->state == HttpRequest::State::ReadingStatus)
        if ((error = !request->readStatus(socket)))
            qWarning() << "Invalid Status";

    if (!error && request->state == HttpRequest::State::ReadingHeader)
        if ((error = !request->readHeader(socket)))
            qWarning() << "Invalid Header";

    if (error) {
        socket->disconnectFromHost();
        mClients.remove(socket);
    } else if (!request->url.isEmpty()) {
        Q_ASSERT(request->state != HttpRequest::State::ReadingUrl);
        answerClient(socket, request->url);
        mClients.remove(socket);
    }
}

void HbAuth2HttpReplyHandler::answerClient(QTcpSocket* socket, const QUrl& url) {
    if (!url.path().startsWith(QLatin1String("/"))) {
        qWarning() << "Invalid request:" << url.toString();
    } else {
        QVariantMap receivedData;
        const QUrlQuery query(url.query());
        const auto items = query.queryItems();
        for (auto it = items.begin(), end = items.end(); it != end; ++it)
            receivedData.insert(it->first, it->second);
        emit callbackReceived(receivedData);

        const QByteArray html = QString(R"html(
            <html>
            <head><title>%1</title><script>window.close();</script></head>
            <body>Operation done, feel free to close this page.</body>
            </html>
        )html")
                                    .arg(QCoreApplication::applicationName())
                                    .toUtf8();

        const QByteArray htmlSize = QString::number(html.size()).toUtf8();
        const QByteArray replyMessage = QByteArrayLiteral("HTTP/1.0 200 OK \r\n"
                                                          "Content-Type: text/html; "
                                                          "charset=\"utf-8\"\r\n"
                                                          "Content-Length: ")
                                        + htmlSize + QByteArrayLiteral("\r\n\r\n") + html;

        socket->write(replyMessage);
        socket->flush();
    }
    socket->disconnectFromHost();
}
