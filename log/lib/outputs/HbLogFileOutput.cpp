// Qt
#include <QtCore/QDateTime>
#include <QtCore/QDir>
#include <QtCore/QTextStream>
// Hb
#include <HbLogMessage.h>
#include <outputs/HbLogFileOutput.h>

using namespace hb::log;

const quint32 HbLogFileOutput::msMaxFileSize = 100000000; // 100 Mo.
const QString HbLogFileOutput::msDefaultPath = "log";

HbLogFileOutput::HbLogFileOutput(const QString& path, quint32 maxSize, QObject* parent) : HbLogAbstractOutput(parent) {
    mPath = (path.isEmpty() ? msDefaultPath : path);

    maxSize *= 1000000; // To bytes.
    mMaxSize = ((maxSize > msMaxFileSize) ? msMaxFileSize : maxSize);
    if (maxSize == 0) {
        mMaxSize = msMaxFileSize;
    }
}

HbLogFileOutput::~HbLogFileOutput() {
    closeLogFile();
}

void HbLogFileOutput::init() {
    mFile.reset(new QFile());
    mStream.reset(new QTextStream());
    createLogFile();
}

void HbLogFileOutput::closeLogFile() {
    mStream->setDevice(0);
    if (mFile->isOpen()) {
        mFile->flush();
        mFile->close();
    }
}

void HbLogFileOutput::createLogFile() {
    closeLogFile();

    QString filename = QDateTime::currentDateTime().toString(QStringLiteral("yyyy-MM-dd_hh-mm-ss-zzz"));
    QString filepath = QStringLiteral("%1/%2.log").arg(mPath).arg(filename);

    mFile->setFileName(filepath);

    std::cout << "HbLog: file created " << mFile->fileName().toStdString().c_str() << std::endl;

    if (!QDir(mPath).exists()) {
        QDir().mkdir(mPath);
    }

    if (!mFile->open(QIODevice::WriteOnly | QIODevice::Text)) {
        std::cerr << "HbLog: error while opening file " << qPrintable(mFile->fileName()) << ": "
                  << qPrintable(mFile->errorString());
    }

    mStream->setDevice(mFile.data());
}

void HbLogFileOutput::processMessage(const HbLogMessagePtr& message) {
    if (mFile->size() >= mMaxSize) {
        createLogFile();
    }

    if (mFile->isWritable()) {
        (*mStream.data()) << HbLogMessage::toRaw(*message.data()) << QChar(QChar::LineFeed);
        mStream->flush();
    }
}
