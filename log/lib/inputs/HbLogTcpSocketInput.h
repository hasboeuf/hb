/****************************************************************************
** Copyright (C) 2012-2015 Adrien Gavignet (hasboeuf)
** Contact: adrien.gavignet@gmail.com
**
** This file is part of the Hb module. Provided "AS IS", WITHOUT WARRANTIES
** OR CONDITIONS OF ANY KIND, either express or implied.
****************************************************************************/

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
class HbLogTcpSocketInput final : public HbLogAbstractInput {
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

private
    callbacks :

        void
        onReadyRead();
    void onClientDisconnected();

private:
    quint16 mPort;
    qint32 mExpected;
    QScopedPointer<QTcpServer> mTcpServer;
    QSet<QTcpSocket*> mClients;
};
} // namespace log
} // namespace hb

#endif
