/****************************************************************************
** Copyright (C) 2012-2015 Adrien Gavignet (hasboeuf)
** Contact: adrien.gavignet@gmail.com
**
** This file is part of the Hb module. Provided "AS IS", WITHOUT WARRANTIES
** OR CONDITIONS OF ANY KIND, either express or implied.
****************************************************************************/

#ifndef HBLOGUDPSOCKETOUTPUT_H
#define HBLOGUDPSOCKETOUTPUT_H

/*! \file HbLogTcpSocketInput.h */

// Qt
#include <QtCore/QScopedPointer>
// Hb
#include <HbGlobal.h>
// Local
#include <outputs/HbLogAbstractOutput.h>

class QUdpSocket;

namespace hb {
namespace log {
class HbLogMessage;

/*!
 * TODOC
 */
class HbLogUdpSocketOutput final : public HbLogAbstractOutput {
    Q_OBJECT
    Q_DISABLE_COPY(HbLogUdpSocketOutput)

public:
    HbLogUdpSocketOutput() = delete;
    HbLogUdpSocketOutput(const QString& ip, quint16 port, QObject* parent = nullptr);
    virtual ~HbLogUdpSocketOutput();

    quint16 port() const;

protected:
    void init() override;
    void processMessage(const HbLogMessagePtr& message) override;

private:
    QScopedPointer<QUdpSocket> mUdpSocket;
    QString mIp;
    quint16 mPort;
};
} // namespace log
} // namespace hb

#endif // HBLOGUDPSOCKETOUTPUT_H
