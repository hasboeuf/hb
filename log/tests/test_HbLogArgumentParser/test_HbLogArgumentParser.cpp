#include <QtCore/QObject>
#include <QtTest>

#include <HbLogArgumentParser.h>

using namespace hb::log;

class TestHbLogArgumentParser : public QObject {
    Q_OBJECT

private slots:

    void testCheckIsConsoleOutput_data() {
        QTest::addColumn<QString>("input");
        QTest::addColumn<bool>("valid");
        QTest::addRow("ok") << "--hblog-output-console" << true;
        QTest::addRow("wrong") << "--hblog-input-console" << false;
        QTest::addRow("empty") << "" << false;
        QTest::addRow("off-topic") << "appname" << false;
    }

    void testCheckIsConsoleOutput() {
        QFETCH(QString, input);
        QFETCH(bool, valid);

        HbLogArgumentParser parser;
        parser.setInput(input);

        QCOMPARE(parser.checkIsConsoleOutput(), valid);
    }

    void testCheckIsFileOutput_data() {
        QTest::addColumn<QString>("input");
        QTest::addColumn<bool>("valid");
        QTest::addColumn<QString>("filePath");
        QTest::addColumn<quint32>("fileMaxSize");
        QTest::addRow("ok") << "--hblog-output-file:toto:32" << true << "toto" << (quint32)32;
        QTest::addRow("missing one arg") << "--hblog-output-file:toto:" << false << "" << (quint32)0;
        QTest::addRow("missing all args") << "--hblog-output-file::" << false << "" << (quint32)0;
        QTest::addRow("wrong") << "--hblog-input-file:toto:" << false << "" << (quint32)0;
        QTest::addRow("off-topic") << "appname" << false << "" << (quint32)0;
    }

    void testCheckIsFileOutput() {
        QFETCH(QString, input);
        QFETCH(bool, valid);
        QFETCH(QString, filePath);
        QFETCH(quint32, fileMaxSize);

        HbLogArgumentParser parser;
        parser.setInput(input);

        QCOMPARE(parser.checkIsFileOutput(), valid);
        QCOMPARE(parser.filePath(), filePath);
        QCOMPARE(parser.fileMaxSize(), fileMaxSize);
    }

    void testCheckIsLocalOutput_data() {
        QTest::addColumn<QString>("input");
        QTest::addColumn<bool>("valid");
        QTest::addColumn<QString>("serverName");
        QTest::addRow("ok") << "--hblog-output-local:hblog" << true << "hblog";
        QTest::addRow("missing one arg") << "--hblog-output-local:" << false << "";
        QTest::addRow("wrong") << "--hblog-input-local:" << false << "";
        QTest::addRow("off-topic") << "appname" << false << "";
    }

    void testCheckIsLocalOutput() {
        QFETCH(QString, input);
        QFETCH(bool, valid);
        QFETCH(QString, serverName);

        HbLogArgumentParser parser;
        parser.setInput(input);

        QCOMPARE(parser.checkIsLocalOutput(), valid);
        QCOMPARE(parser.serverName(), serverName);
    }

    void testCheckIsTcpSocketOutput_data() {
        QTest::addColumn<QString>("input");
        QTest::addColumn<bool>("valid");
        QTest::addColumn<QString>("ip");
        QTest::addColumn<quint16>("port");
        QTest::addRow("ok") << "--hblog-output-tcp:192.168.1.89:8000" << true << "192.168.1.89" << (quint16)8000;
        QTest::addRow("missing one arg") << "--hblog-output-tcp:192.168.1.89:" << false << "" << (quint16)0;
        QTest::addRow("missing all args") << "--hblog-output-tcp::" << false << "" << (quint16)0;
        QTest::addRow("off-topic") << "appname" << false << "" << (quint16)0;
    }

    void testCheckIsTcpSocketOutput() {
        QFETCH(QString, input);
        QFETCH(bool, valid);
        QFETCH(QString, ip);
        QFETCH(quint16, port);

        HbLogArgumentParser parser;
        parser.setInput(input);

        QCOMPARE(parser.checkIsTcpSocketOutput(), valid);
        QCOMPARE(parser.ip(), ip);
        QCOMPARE(parser.port(), port);
    }

    void testCheckIsUdpSocketOutput_data() {
        QTest::addColumn<QString>("input");
        QTest::addColumn<bool>("valid");
        QTest::addColumn<QString>("ip");
        QTest::addColumn<quint16>("port");
        QTest::addRow("ok") << "--hblog-output-udp:127.0.0.1:4000" << true << "127.0.0.1" << (quint16)4000;
        QTest::addRow("missing one arg") << "--hblog-output-udp:127.0.0.1:" << false << "" << (quint16)0;
        QTest::addRow("missing all args") << "--hblog-output-udp::" << false << "" << (quint16)0;
    }

    void testCheckIsUdpSocketOutput() {
        QFETCH(QString, input);
        QFETCH(bool, valid);
        QFETCH(QString, ip);
        QFETCH(quint16, port);

        HbLogArgumentParser parser;
        parser.setInput(input);

        QCOMPARE(parser.checkIsUdpSocketOutput(), valid);
        QCOMPARE(parser.ip(), ip);
        QCOMPARE(parser.port(), port);
    }

    void testCheckIsLocalInput_data() {
        QTest::addColumn<QString>("input");
        QTest::addColumn<bool>("valid");
        QTest::addColumn<QString>("serverName");
        QTest::addRow("ok") << "--hblog-input-local:hblog" << true << "hblog";
        QTest::addRow("missing one arg") << "--hblog-input-local:" << false << "";
        QTest::addRow("off-topic") << "appname" << false << "";
    }

    void testCheckIsLocalInput() {
        QFETCH(QString, input);
        QFETCH(bool, valid);
        QFETCH(QString, serverName);

        HbLogArgumentParser parser;
        parser.setInput(input);

        QCOMPARE(parser.checkIsLocalInput(), valid);
        QCOMPARE(parser.serverName(), serverName);
    }

    void testCheckIsTcpSocketInput_data() {
        QTest::addColumn<QString>("input");
        QTest::addColumn<bool>("valid");
        QTest::addColumn<quint16>("port");
        QTest::addRow("ok") << "--hblog-input-tcp:4000" << true << (quint16)4000;
        QTest::addRow("missing one arg") << "--hblog-input-tcp:" << false << (quint16)0;
        QTest::addRow("wrong") << "--hblog-output-tcp:4000" << false << (quint16)0;
    }

    void testCheckIsTcpSocketInput() {
        QFETCH(QString, input);
        QFETCH(bool, valid);
        QFETCH(quint16, port);

        HbLogArgumentParser parser;
        parser.setInput(input);

        QCOMPARE(parser.checkIsTcpSocketInput(), valid);
        QCOMPARE(parser.port(), port);
    }

    void testCheckIsUdpSocketInput_data() {
        QTest::addColumn<QString>("input");
        QTest::addColumn<bool>("valid");
        QTest::addColumn<quint16>("port");
        QTest::addRow("ok") << "--hblog-input-udp:4000" << true << (quint16)4000;
        QTest::addRow("empty") << "" << false << (quint16)0;
        QTest::addRow("no args") << "--hblog-input-udp" << false << (quint16)0;
    }

    void testCheckIsUdpSocketInput() {
        QFETCH(QString, input);
        QFETCH(bool, valid);
        QFETCH(quint16, port);

        HbLogArgumentParser parser;
        parser.setInput(input);

        QCOMPARE(parser.checkIsUdpSocketInput(), valid);
        QCOMPARE(parser.port(), port);
    }
};

QTEST_APPLESS_MAIN(TestHbLogArgumentParser)
#include "test_HbLogArgumentParser.moc"
