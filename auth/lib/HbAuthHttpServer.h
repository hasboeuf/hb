#ifndef HBAUTHHTTPSERVER_H
#define HBAUTHHTTPSERVER_H

// Qt
#include <QtNetwork/QSslConfiguration>
#include <QtNetwork/QTcpServer>

namespace hb {
namespace auth {

class HbAuthHttpServer : public QTcpServer {
    Q_OBJECT
public:
    HbAuthHttpServer(quint16 port, bool sslEnabled, QObject* parent = nullptr);

signals:
    void socketConnected(QTcpSocket* socket);

protected:
    void incomingConnection(qintptr handle) override;

private:
    void onNewConnection();

    quint16 mPort;
    bool mSslEnabled;
    QSslConfiguration mSslConfiguration;
};

} // namespace auth
} // namespace hb

#endif // HBAUTHHTTPSERVER_H
