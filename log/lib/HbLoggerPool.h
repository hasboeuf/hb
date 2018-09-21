/****************************************************************************
** Copyright (C) 2012-2015 Adrien Gavignet (hasboeuf)
** Contact: adrien.gavignet@gmail.com
**
** This file is part of the Hb module. Provided "AS IS", WITHOUT WARRANTIES
** OR CONDITIONS OF ANY KIND, either express or implied.
****************************************************************************/

#ifndef HBLOGGERPOOL_H
#define HBLOGGERPOOL_H

/*! \file HbLoggerPool.h */

// Qt
#include <QtCore/QHash>
#include <QtCore/QObject>
// Hb
#include <HbGlobal.h>
#include <HbLog.h>

class QTimer;

namespace hb {
namespace log {

class HbLogAbstractOutput;
class HbLogAbstractInput;
class HbLogAbstractOutput;
class HbLogGuiNotifier;
class HbLogMessage;

/*!
 * Internal class, TODOC.
 */
class HbLoggerPool final : public QObject {
    Q_OBJECT
    Q_DISABLE_COPY(HbLoggerPool)

private:
    static const quint16 MAX_CAPACITY = 500;
    static const quint16 TCP_PORT_MIN = 1024;
    // static const quint16 TCP_PORT_MAX = 65535; Useless as quint16 protects the range.

public:
    HbLoggerPool();
    virtual ~HbLoggerPool();

    void addUdpSocketInput(quint16 port);
    void addTcpSocketInput(quint16 port);
    void addLocalSocketInput(const QString& name);

    void addConsoleOutput();
    void addGuiOutput(HbLogGuiNotifier* notifier);
    void addFileOutput(const QString& path, quint32 max_size);
    void addUdpSocketOutput(const QString& ip, quint16 port);
    void addTcpSocketOutput(const QString& ip, quint16 port);
    void addLocalSocketOutput(const QString& name);

    bool enqueueMessage(QList<HbLogMessage*>& buffer);

public slots:
    void running();

private
    callbacks : void onInputMessageReceived(HbLogMessage* message);
    // From QThread

    void process();

private:
    QAtomicInt mAtomic;

    QTimer* mpClock;
    qint32 mCapacity;

    QList<HbLogMessage*> mLoggerStream;
    QList<HbLogMessage*> mInputsStream;

    QHash<quint32, HbLogAbstractInput*> mInputs;
    QHash<quint32, HbLogAbstractOutput*> mOutputs;
};
} // namespace log
} // namespace hb

#endif // HBLOGGERPOOL_H
