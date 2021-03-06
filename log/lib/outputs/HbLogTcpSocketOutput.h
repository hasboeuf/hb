#ifndef HBLOGTCPSOCKETOUTPUT_H
#define HBLOGTCPSOCKETOUTPUT_H

/*! \file HbLogTcpSocketOutput.h */

// Qt
#include <QtCore/QScopedPointer>
// Hb
#include <outputs/HbLogAbstractOutput.h>

class QTcpSocket;

namespace hb {
namespace log {

/*!
 * TODOC
 * \brief The %HbLogTcpSocketOutput class defines a tcp socket output.
 *
 * %HbLogTcpSocketOutput inherits from HbLogAbstractOutput.\n
 */
class HbLogTcpSocketOutput : public HbLogAbstractOutput {
    Q_OBJECT
    Q_DISABLE_COPY(HbLogTcpSocketOutput)

public:
    HbLogTcpSocketOutput() = delete;
    HbLogTcpSocketOutput(const QString& ip, quint16 port, QObject* parent = nullptr);
    virtual ~HbLogTcpSocketOutput();

    QString ip() const;
    quint16 port() const;

protected:
    void init() override;
    void processMessage(const HbLogMessagePtr& message) override;

private:
    void onReconnection();

    QScopedPointer<QTcpSocket> mTcpSocket;
    QString mIp;
    quint16 mPort;
};
} // namespace log
} // namespace hb

#endif
