// System
// Qt
#include <QtCore/QCommandLineParser>
#include <QtCore/QCoreApplication>
#include <QtCore/QDateTime>
#include <QtCore/QDebug>
#include <QtCore/QJsonDocument>
#include <QtCore/QJsonObject>
#include <QtCore/QTimer>
#include <QtCore/QVariant>
#include <QtCore/QVariantMap>
// Hb
#include <HbGlobal.h>
#include <core/HbApplicationHelper.h>
#include <core/HbSingleApplication.h>

using namespace hb::tools;

static constexpr char MESSAGE_COMMAND_KEY[] = "command";
static constexpr char MESSAGE_REPEAT_KEY[] = "repeat";
static constexpr char RESPONSE_CODE_KEY[] = "code";
static constexpr char RESPONSE_MESSAGE_KEY[] = "message";

static void setupParser(QCommandLineParser* parser) {
    Q_ASSERT(parser);
    parser->setApplicationDescription(
        QString("%1 - Sample for HbSingleApplication").arg(QCoreApplication::applicationName()));
    parser->addHelpOption();
    parser->addVersionOption();
    parser->addPositionalArgument("command", "Command to execute");
    parser->addOption({MESSAGE_REPEAT_KEY, "Execute command n times", "value"});
}

static QVariantMap messageFromParser(QCommandLineParser* parser) {
    Q_ASSERT(parser);

    auto message = QVariantMap();

    if (parser->positionalArguments().count() == 1) {
        message[MESSAGE_COMMAND_KEY] = parser->positionalArguments().first();
    };
    if (parser->isSet(MESSAGE_REPEAT_KEY)) {
        message[MESSAGE_REPEAT_KEY] = parser->value(MESSAGE_REPEAT_KEY).toInt();
    }

    return message;
}

static QVariant messageHandler(const QVariant& message) {
    QVariantMap order = message.toMap();
    QString command = order.value(MESSAGE_COMMAND_KEY).toString();
    int repeat = order.value(MESSAGE_REPEAT_KEY, 1).toInt();

    if (command.isEmpty()) {
        return QVariant();
    }

    if (command == "stop") {
        QTimer::singleShot(0, []() {
            qDebug() << "ExistingApplication stopping...";
            QCoreApplication::quit();
        });
    }

    for (int i = 0; i < repeat; ++i) {
        qDebug() << QString("ExistingApplication: run operation `%1()`").arg(command);
    }

    return QVariantMap({{RESPONSE_CODE_KEY, "200"}, {RESPONSE_MESSAGE_KEY, "Message treated"}});
}

int main(int argc, char* argv[]) {
    QCoreApplication a(argc, argv);
    a.setApplicationName("SingleApplication");
    a.setOrganizationName("hb");
    a.setOrganizationName("url");
    a.setApplicationVersion("1.0.0");

    QCommandLineParser parser;
    setupParser(&parser);
    parser.process(a);

    auto message = messageFromParser(&parser);

    HbSingleApplication singleApplication;
    if (singleApplication.connectToExistingApplication()) {
        QVariantMap response = singleApplication.sendToExistingApplication(message).toMap();
        qDebug().noquote() << "Response:" << QJsonDocument(QJsonObject::fromVariantMap(response)).toJson();
        return 0;
    }

    singleApplication.setMessageHandlerFunction(messageHandler);
    bool ok = singleApplication.acquireApplication();
    Q_ASSERT(ok);

    messageHandler(message);

    return a.exec();
}
