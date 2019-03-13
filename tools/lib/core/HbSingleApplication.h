#ifndef HBSINGLEAPPLICATION_H
#define HBSINGLEAPPLICATION_H

/*! \file HbSingleApplication.h */

// System
#include <functional>
// Qt
#include <QtCore/QScopedPointer>
#include <QtCore/QVariant>
// Local
#include <HbTools.h>

class QLocalSocket;
class QLocalServer;

namespace hb {
namespace tools {

typedef std::function<QVariant(const QVariant&)> MessageHandlerFunction;

/*!
 * HbSingleApplication provides a way to deal with only one instance of an application.
 *
 * Behind the hood, local sockets are used which as a side effect setup a basic messaging communication.
 *
 * Note: This class is subject to race conditions which could happen between
 *       connectToExistingApplication() and acquireApplication() calls.
 *       It's up to the class user to ensure atomicity between them with a `QLockFile` for example.
 */
class HB_TOOLS_DECL HbSingleApplication {
public:
    HbSingleApplication();
    ~HbSingleApplication();

    /**
     * Check if there is a running application
     * @param msTimeout Number of milliseconds after which attempt is aborted.
     * @return True if there is already an application running, false otherwise.
     */
    bool connectToExistingApplication(int msTimeout = 5000);

    /**
     * Try to be the only one instance of the application and starts listening for messages
     * @return True on success, false otherwise
     * @note setMessageHandlerFunction() should have been called first
     */
    bool acquireApplication();

    /**
     * Send a message to existing instance
     * @param msTimeout Number of milliseconds to wait for the response
     * @return Response as QVariant
     * @note connectToExistingApplication() should have been called first
     */
    QVariant sendToExistingApplication(const QVariant& message, int msTimeout = 5000);

    /**
     * Set function responsible of message handling
     * @param handler Functor
     */
    void setMessageHandlerFunction(MessageHandlerFunction handler);

private:
    void readFromClientSocket(QLocalSocket* socket);
    QScopedPointer<QLocalSocket> mClient;
    QString mServerName;
    QScopedPointer<QLocalServer> mServer;
    MessageHandlerFunction mMessageHandler;
};
} // namespace tools
} // namespace hb

#endif // HBSINGLEAPPLICATION_H
