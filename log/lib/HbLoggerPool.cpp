// Qt
#include <QtCore/QCoreApplication>
#include <QtCore/QMetaObject>
#include <QtCore/QMutexLocker>
#include <QtCore/QThread>
#include <QtCore/QTimer>
// Hb
#include <HbGlobal.h>
#include <HbLogMessage.h>
#include <HbLoggerPool.h>
#include <inputs/HbLogLocalSocketInput.h>
#include <inputs/HbLogTcpSocketInput.h>
#include <inputs/HbLogUdpSocketInput.h>
#include <outputs/HbLogConsoleOutput.h>
#include <outputs/HbLogFileOutput.h>
#include <outputs/HbLogGuiOutput.h>
#include <outputs/HbLogLocalSocketOutput.h>
#include <outputs/HbLogTcpSocketOutput.h>
#include <outputs/HbLogUdpSocketOutput.h>

using namespace hb::log;

HbLoggerPool::HbLoggerPool(QObject* parent) : QObject(parent) {
    mAtomic = 0;
    mCapacity = MAX_CAPACITY;
}

HbLoggerPool::~HbLoggerPool() {
    // Dequeueing events
    QCoreApplication::processEvents(QEventLoop::ExcludeUserInputEvents);

    qDeleteAll(mInputs); // Disconnect inputs.

    while (!mLoggerStream.isEmpty()) {
        process();
        QThread::yieldCurrentThread();
    }

    qDeleteAll(mOutputs);
    qDeleteAll(mLoggerStream);
}

void HbLoggerPool::addUdpSocketInput(quint16 port) {
    QMutexLocker locker(&mMutex);
    HbLogAbstractInput* input = new HbLogUdpSocketInput(port, this);
    input->moveToThread(thread());
    QMetaObject::invokeMethod(input, &HbLogAbstractInput::init);

    connect(input, &HbLogUdpSocketInput::inputMessageReceived, this, &HbLoggerPool::onInputMessageReceived);

    mInputs.insert(input->uid(), input);
    std::cout << "HbLog: added upd input on port " << port << std::endl;
}

void HbLoggerPool::addTcpSocketInput(quint16 port) {
    QMutexLocker locker(&mMutex);
    HbLogAbstractInput* input = new HbLogTcpSocketInput(port, this);
    input->moveToThread(thread());
    QMetaObject::invokeMethod(input, &HbLogAbstractInput::init);

    connect(input, &HbLogUdpSocketInput::inputMessageReceived, this, &HbLoggerPool::onInputMessageReceived);

    mInputs.insert(input->uid(), input);
    std::cout << "HbLog: added tcp input on port " << port << std::endl;
}

void HbLoggerPool::addLocalSocketInput(const QString& name) {
    QMutexLocker locker(&mMutex);
    HbLogAbstractInput* input = new HbLogLocalSocketInput(name, this);
    input->moveToThread(thread());
    QMetaObject::invokeMethod(input, &HbLogAbstractInput::init);

    connect(input, &HbLogUdpSocketInput::inputMessageReceived, this, &HbLoggerPool::onInputMessageReceived);

    mInputs.insert(input->uid(), input);
    std::cout << "HbLog: added local input " << name.toStdString() << std::endl;
}

void HbLoggerPool::addConsoleOutput() {
    QMutexLocker locker(&mMutex);
    HbLogAbstractOutput* output = new HbLogConsoleOutput();
    output->moveToThread(thread());
    QMetaObject::invokeMethod(output, &HbLogAbstractOutput::init);
    mOutputs.insert(output->uid(), output);
    std::cout << "HbLog: added console output" << std::endl;
}

void HbLoggerPool::addGuiOutput(HbLogGuiNotifier* notifier) {
    QMutexLocker locker(&mMutex);
    HbLogAbstractOutput* output = new HbLogGuiOutput(notifier);
    output->moveToThread(thread());
    QMetaObject::invokeMethod(output, &HbLogAbstractOutput::init);
    mOutputs.insert(output->uid(), output);
    std::cout << "HbLog: added gui output for notifier " << notifier << std::endl;
}

void HbLoggerPool::addFileOutput(const QString& dir, quint32 maxSize) {
    QMutexLocker locker(&mMutex);
    HbLogAbstractOutput* output = new HbLogFileOutput(dir, maxSize);
    output->moveToThread(thread());
    QMetaObject::invokeMethod(output, &HbLogAbstractOutput::init);
    mOutputs.insert(output->uid(), output);
    std::cout << "HbLog: added file output in " << dir.toStdString() << std::endl;
}

void HbLoggerPool::addUdpSocketOutput(const QString& ip, quint16 port) {
    QMutexLocker locker(&mMutex);
    HbLogAbstractOutput* output = new HbLogUdpSocketOutput(ip, port);
    output->moveToThread(thread());
    QMetaObject::invokeMethod(output, &HbLogAbstractOutput::init);
    mOutputs.insert(output->uid(), output);
    std::cout << "HbLog: added upd output on " << ip.toStdString() << ":" << port << std::endl;
}

void HbLoggerPool::addTcpSocketOutput(const QString& ip, quint16 port) {
    QMutexLocker locker(&mMutex);
    HbLogAbstractOutput* output = new HbLogTcpSocketOutput(ip, port);
    output->moveToThread(thread());
    QMetaObject::invokeMethod(output, &HbLogAbstractOutput::init);
    mOutputs.insert(output->uid(), output);
    std::cout << "HbLog: added tcp output on " << ip.toStdString() << ":" << port << std::endl;
}

void HbLoggerPool::addLocalSocketOutput(const QString& name) {
    QMutexLocker locker(&mMutex);
    HbLogAbstractOutput* output = new HbLogLocalSocketOutput(name);
    output->moveToThread(thread());
    QMetaObject::invokeMethod(output, &HbLogAbstractOutput::init);
    mOutputs.insert(output->uid(), output);
    std::cout << "HbLog: added local output " << name.toStdString() << std::endl;
}

bool HbLoggerPool::enqueueMessage(QList<HbLogMessage*>& buffer) {
    if (mAtomic.testAndSetOrdered(0, 1)) {
        while (!buffer.isEmpty()) {
            if (mLoggerStream.size() == mCapacity) {
                delete mLoggerStream.takeFirst();
            }

            mLoggerStream.push_back(buffer.takeFirst());
        }
        QTimer::singleShot(0, this, &HbLoggerPool::process);

        mAtomic.fetchAndStoreOrdered(0);
        return true;
    }
    return false;
}

void HbLoggerPool::running() {
}

void HbLoggerPool::onInputMessageReceived(HbLogMessage* message) {
    mInputsStream.push_back(message);
    QTimer::singleShot(0, this, &HbLoggerPool::process);
}

void HbLoggerPool::process() {
    if (mAtomic.testAndSetOrdered(0, 1)) {
        // Dequeue messages coming from inputs.
        while (!mInputsStream.isEmpty()) {
            if (mLoggerStream.size() == mCapacity) {
                delete mLoggerStream.takeFirst();
            }

            mLoggerStream.push_back(mInputsStream.takeFirst());
        }

        // Dequeue general message list.
        if (mOutputs.size() > 0) {
            while (!mLoggerStream.isEmpty()) {
                HbLogMessagePtr message(mLoggerStream.takeFirst());

                for (HbLogAbstractOutput* output : mOutputs.values()) {
                    output->processMessage(message);
                }
            }
        }

        mAtomic.fetchAndStoreOrdered(0);
    } else {
        QTimer::singleShot(0, this, &HbLoggerPool::process);
    }
}
