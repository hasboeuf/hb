#ifndef HBTCPSOCKETHANDLER_H
#define HBTCPSOCKETHANDLER_H

/*! \file HbTcpSocketHandler.h */

// Qt
#include <QtCore/QObject>
// Hb
#include <HbGlobal.h>
// Local
#include <com/HbSocketHandler.h>
#include <com/tcp/HbTcpServer.h> // Covariance.

namespace hb {
namespace network {
/*!
 * TODOC
 */
class HbTcpSocketHandler : public HbSocketHandler {
    Q_OBJECT
    Q_DISABLE_COPY(HbTcpSocketHandler)
    friend class HbTcpServer;

public:
    virtual void onNewPendingConnection(qint32 socket_descriptor) override;

protected:
    HbTcpSocketHandler(HbTcpServer* server);
    virtual ~HbTcpSocketHandler();

    virtual HbTcpServer* server() const override;

    virtual void init();
    virtual void reset();

private:
    HbTcpServer* mServer;
};
} // namespace network
} // namespace hb

#endif // HBTCPSOCKETHANDLER_H
