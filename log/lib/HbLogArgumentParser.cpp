#include <HbLogArgumentParser.h>

using namespace hb::log;

static constexpr char CONSOLE_PATTERN[] = "--hblog-output-console";
static constexpr char OUTPUT_FILE_PATTERN[] = "--hblog-output-file:(\\S+):(\\d+)";
static constexpr char OUTPUT_LOCAL_PATTERN[] = "--hblog-output-local:(\\w+)";
static constexpr char OUTPUT_TCP_PATTERN[] = "--hblog-output-tcp:(\\S+):(\\d+)";
static constexpr char OUTPUT_UDP_PATTERN[] = "--hblog-output-udp:(\\S+):(\\d+)";
static constexpr char INPUT_LOCAL_PATTERN[] = "--hblog-input-local:(\\w+)";
static constexpr char INPUT_TCP_PATTERN[] = "--hblog-input-tcp:(\\d+)";
static constexpr char INPUT_UDP_PATTERN[] = "--hblog-input-udp:(\\d+)";

void HbLogArgumentParser::setInput(const QString& input) {
    mInput = input;
    mFilePath.clear();
    mFileMaxSize = 0;
    mServerName.clear();
    mIp.clear();
    mPort = 0;
}

bool HbLogArgumentParser::checkIsConsoleOutput() {
    return mInput == CONSOLE_PATTERN;
}

bool HbLogArgumentParser::checkIsFileOutput() {
    QRegExp rx(OUTPUT_FILE_PATTERN);
    if (rx.indexIn(mInput) < 0) {
        return false;
    }
    if (rx.captureCount() != 2) {
        return false;
    }

    bool ok = true;
    mFilePath = rx.cap(1);
    mFileMaxSize = rx.cap(2).toInt(&ok);
    return ok;
}

bool HbLogArgumentParser::checkIsLocalOutput() {
    QRegExp rx(OUTPUT_LOCAL_PATTERN);
    if (rx.indexIn(mInput) < 0) {
        return false;
    }
    if (rx.captureCount() != 1) {
        return false;
    }

    mServerName = rx.cap(1);
    return true;
}

bool HbLogArgumentParser::checkIsTcpSocketOutput() {
    QRegExp rx(OUTPUT_TCP_PATTERN);
    if (rx.indexIn(mInput) < 0) {
        return false;
    }
    if (rx.captureCount() != 2) {
        return false;
    }

    bool ok = true;
    mIp = rx.cap(1);
    mPort = rx.cap(2).toInt(&ok);
    return ok;
}

bool HbLogArgumentParser::checkIsUdpSocketOutput() {
    QRegExp rx(OUTPUT_UDP_PATTERN);
    if (rx.indexIn(mInput) < 0) {
        return false;
    }
    if (rx.captureCount() != 2) {
        return false;
    }

    bool ok = true;
    mIp = rx.cap(1);
    mPort = rx.cap(2).toInt(&ok);
    return ok;
}

bool HbLogArgumentParser::checkIsLocalInput() {
    QRegExp rx(INPUT_LOCAL_PATTERN);
    if (rx.indexIn(mInput) < 0) {
        return false;
    }
    if (rx.captureCount() != 1) {
        return false;
    }

    mServerName = rx.cap(1);
    return true;
}

bool HbLogArgumentParser::checkIsTcpSocketInput() {
    QRegExp rx(INPUT_TCP_PATTERN);
    if (rx.indexIn(mInput) < 0) {
        return false;
    }
    if (rx.captureCount() != 1) {
        return false;
    }

    bool ok = true;
    mPort = rx.cap(1).toInt(&ok);
    return ok;
}

bool HbLogArgumentParser::checkIsUdpSocketInput() {
    QRegExp rx(INPUT_UDP_PATTERN);
    if (rx.indexIn(mInput) < 0) {
        return false;
    }
    if (rx.captureCount() != 1) {
        return false;
    }

    bool ok = true;
    mPort = rx.cap(1).toInt(&ok);
    return ok;
}

QString HbLogArgumentParser::filePath() const {
    return mFilePath;
}

quint32 HbLogArgumentParser::fileMaxSize() const {
    return mFileMaxSize;
}

QString HbLogArgumentParser::serverName() const {
    return mServerName;
}

QString HbLogArgumentParser::ip() const {
    return mIp;
}

quint16 HbLogArgumentParser::port() const {
    return mPort;
}
