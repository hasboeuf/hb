#ifndef HBLOGUDPSOCKETINPUT_H
#define HBLOGUDPSOCKETINPUT_H

/*! \file HbLogUdpSocketInput.h */

// Qt
#include <QtCore/QScopedPointer>
// Local
#include <inputs/HbLogAbstractInput.h>

class QUdpSocket;

namespace hb {
namespace log {
class HbLogMessage;

/*!
 * TODOC
 */
class HbLogUdpSocketInput : public HbLogAbstractInput {
    Q_OBJECT
    Q_DISABLE_COPY(HbLogUdpSocketInput)

public:
    HbLogUdpSocketInput() = delete;
    HbLogUdpSocketInput(quint16 port, QObject* parent = nullptr);
    virtual ~HbLogUdpSocketInput();

    quint16 port() const;

protected:
    void init() override;

private:
    void onReconnection();
    void onReadyRead();

    qint32 mExpected;
    quint16 mPort;
    QScopedPointer<QUdpSocket> mUdpSocket;
};
} // namespace log
} // namespace hb

#endif // HBLOGUDPSOCKETINPUT_H
