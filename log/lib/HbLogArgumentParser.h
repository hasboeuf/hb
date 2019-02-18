#ifndef HBLOGARGUMENTPARSER_H
#define HBLOGARGUMENTPARSER_H

/*! \file HbLogMessage.h */

// Hb
#include <HbLogContext.h>

namespace hb {
namespace log {
/*!
 * HbLogArgumentParser class handles HbLog arguments processing.
 */
class HB_LOG_DECL HbLogArgumentParser {
public:
    HbLogArgumentParser() = default;

    void setInput(const QString& input);

    bool checkIsConsoleOutput();
    bool checkIsFileOutput();
    bool checkIsLocalOutput();
    bool checkIsTcpSocketOutput();
    bool checkIsUdpSocketOutput();
    bool checkIsLocalInput();
    bool checkIsTcpSocketInput();
    bool checkIsUdpSocketInput();

    QString filePath() const;
    quint32 fileMaxSize() const;
    QString serverName() const;
    QString ip() const;
    quint16 port() const;

private:
    QString mInput;
    QString mFilePath;
    quint32 mFileMaxSize = 0;
    QString mServerName;
    QString mIp;
    quint16 mPort = 0;
};
} // namespace log
} // namespace hb

#endif // HBLOGMESSAGE_H
