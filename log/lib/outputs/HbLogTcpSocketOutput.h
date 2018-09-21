/****************************************************************************
** Copyright (C) 2012-2015 Adrien Gavignet (hasboeuf)
** Contact: adrien.gavignet@gmail.com
**
** This file is part of the Hb module. Provided "AS IS", WITHOUT WARRANTIES
** OR CONDITIONS OF ANY KIND, either express or implied.
****************************************************************************/

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
class HbLogTcpSocketOutput final : public HbLogAbstractOutput {
    Q_OBJECT
    Q_DISABLE_COPY(HbLogTcpSocketOutput)

public:
    HbLogTcpSocketOutput() = delete;
    HbLogTcpSocketOutput(const QString& ip, quint16 port, QObject* parent = nullptr);
    virtual ~HbLogTcpSocketOutput();

    const QString& ip() const;
    quint16 port() const;

protected:
    void init() override;
    void processMessage(const HbLogMessagePtr& message) override;

private slots:
    void onReconnection();

private:
    QScopedPointer<QTcpSocket> mTcpSocket;
    QString mIp;
    quint16 mPort;
};
} // namespace log
} // namespace hb

#endif
