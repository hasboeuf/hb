#ifndef HBLOGTCPSOCKETINPUT_H
#define HBLOGTCPSOCKETINPUT_H

/*! \file HbLogTcpSocketInput.h */

// Qt
#include <QtCore/QScopedPointer>
// Hb
#include <HbGlobal.h>
// Local
#include <inputs/HbLogAbstractInput.h>

class QTcpServer;
class QTcpSocket;

namespace hb {
namespace log {
class HbLogMessage;

/*!
 * TODOC
 * \brief The %HbLogTcpSocketInput class defines a tcp server input.
 */
class HbLogTcpSocketInput : public HbLogAbstractInput {
    Q_OBJECT
    Q_DISABLE_COPY(HbLogTcpSocketInput)

public:
    HbLogTcpSocketInput() = delete;
    HbLogTcpSocketInput(quint16 port, QObject* parent);
    virtual ~HbLogTcpSocketInput();

    quint16 port() const;

protected:
    void init() override;

private:
    void onNewConnection();
    void onReadyRead();
    void onClientDisconnected();

    quint16 mPort;
    qint32 mExpected;
    QScopedPointer<QTcpServer> mTcpServer;
    QSet<QTcpSocket*> mClients;
};
} // namespace log
} // namespace hb

#endif
