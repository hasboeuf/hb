#ifndef HBLINKLOCALSERVER_H
#define HBLINKLOCALSERVER_H

/*! \file HbLinkLocalServer.h */

// Qt
#include <QtCore/QMap>
#include <QtCore/QString>
#include <QtNetwork/QTcpServer>
// Hb
#include <HbLink.h>

namespace hb {
namespace link {

/*!
 * HbLinkLocalServer listens a local port to catch http response.
 * It is used on client side to get the auth code.
 */
class HB_LINK_DECL HbLinkLocalServer : public QTcpServer {
    Q_OBJECT

public:
    explicit HbLinkLocalServer(QObject* parent = nullptr);
    ~HbLinkLocalServer() = default;

signals:
    /*!
     * Triggered when an http response is caught.
     * \param response Response data. Key: OAuth markup name, value: associated value.
     */
    void responseReceived(QHash<QString, QString> response);

private:
    void onIncomingConnection();
    void onReadyRead();

    QHash<QString, QString> parseResponse(QByteArray& data);
};
} // namespace link
} // namespace hb

#endif // HBLINKLOCALSERVER_H
