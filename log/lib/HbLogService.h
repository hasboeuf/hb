#ifndef HBLOGSERVICE_H
#define HBLOGSERVICE_H

/*! \file HbLogService.h */

// Qt
#include <QtCore/QDebug>
#include <QtCore/QThreadStorage>
// Hb
#include <HbGlobal.h>
#include <HbLog.h>
#include <HbLogContext.h>
#include <HbLogger.h>

namespace hb {
namespace log {
class HbLoggerInputs;
class HbLoggerOutputs;
class HbLogManager;
class HbLogGuiNotifier;

/*!
 * HbLogService is the front-end interface of HbLog.
 * HbLogService is a threaded-singleton, that means it can be used from anywhere without any worries.
 * Features:
 * - Set pattern of log messages.
 * - Add/Remove log in/outputs.
 */
namespace HbLogService {
void install(const QString& logPattern = QString());

void print(HbLogger::Level level, const HbLogContext& context, const QString& message);

/*!
 * Process list of args for HbLog.
 * Add in/output according to args.
 *
 * Each argument must fit the following usage (otherwise it is ignored).
 * Usage:
 * --hblog-output-console
 * --hblog-output-file:dir:file_max_size_mo
 * --hblog-output-local:name
 * --hblog-output-tcp:ip:port
 * --hblog-output-udp:ip:port
 * --hblog-input-local:name
 * --hblog-input-tcp:port
 * --hblog-input-udp:port
 */
void processArgs(QStringList args);

/*!
 * Request to add a udp socket input.
 * \param port Server port to connect.
 */
void addUdpSocketInput(quint16 port);

/*!
 * Request to add a tcp server input.
 * \param port Listening port.
 */
void addTcpSocketInput(quint16 port);

/*!
 * Request to add a local server input.
 * \param name Server name (defaulted on DEFAULT_LOCAL_SERVER_NAME).
 */
void addLocalSocketInput(const QString& name = QString());

/*!
 * Request to add a console output.
 * Only one console per application is allowed.
 */
void addConsoleOutput();

/*!
 * Request to add a gui output.
 * \param notifier Gui notifier to connect.
 */
void addGuiOutput(HbLogGuiNotifier* notifier);

/*!
 * Request to add a file output.
 * \param dir Directory to put log files (according to QDir path).
 * \param max_size Max size of log file in Mo (if 0, msMaxFileSize (=100 Mo) will be used).
 */
void addFileOutput(const QString& dir, quint32 max_size = 0);

/*!
 * Request to add a udp socket output.
 * \param port Port to connect.
 */
void addUdpSocketOutput(const QString& ip, quint16 port);

/*!
 * Request to add a tcp socket output.
 * \param ip Ip of the log server.
 * \param port Server port to connect.
 */
void addTcpSocketOutput(const QString& ip, quint16 port);

/*!
 * Request to add a local socket output.
 * \param name Server name (defaulted on DEFAULT_LOCAL_SERVER_NAME).
 */
void addLocalSocketOutput(const QString& name = QString());
} // namespace HbLogService
} // namespace log
} // namespace hb

#endif // HBLOGSERVICE_H
