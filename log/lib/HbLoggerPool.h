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
class HbLoggerPool : public QObject {
    Q_OBJECT
    Q_DISABLE_COPY(HbLoggerPool)

public:
    HbLoggerPool(QObject* parent = nullptr);
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

    void running();

private:
    void onInputMessageReceived(HbLogMessage* message);
    // From QThread

    void process();

    static const quint16 MAX_CAPACITY = 500;
    static const quint16 TCP_PORT_MIN = 1024;
    // static const quint16 TCP_PORT_MAX = 65535; Useless as quint16 protects the range.

    QAtomicInt mAtomic;

    QTimer* mClock;
    qint32 mCapacity;

    QList<HbLogMessage*> mLoggerStream;
    QList<HbLogMessage*> mInputsStream;

    QHash<quint32, HbLogAbstractInput*> mInputs;
    QHash<quint32, HbLogAbstractOutput*> mOutputs;
};
} // namespace log
} // namespace hb

#endif // HBLOGGERPOOL_H
