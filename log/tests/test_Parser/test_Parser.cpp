#include <QtTest>
#include <QtCore/QObject>

class TestParser : public QObject {
    Q_OBJECT

private slots:

    void testOutputConsole_data()
    {
        QTest::addColumn<QString>("input");
        QTest::addColumn<bool>("success");
        QTest::addRow("ok") << "--hblog-output-console" << true;
    }

    void testOutputConsole() {
        QFETCH(QString, input);
        QFETCH(bool, success);

        bool result = (input == "--hblog-output-console");

        QCOMPARE( success, result );
    }

    void testTcpOutput_data()
    {
        QTest::addColumn<QString>("input");
        QTest::addColumn<QString>("ip");
        QTest::addColumn<quint16>("port");
        QTest::addRow("ok") << "--hblog-output-tcp:127.0.0.1:3000" << "127.0.0.1" << ( quint16 ) 3000;
        QTest::addRow("ok") << "--hblog-output-tcp:localhost:65200" << "localhost" << ( quint16 ) 65200;
    }

    void testTcpOutput() {
        QFETCH(QString, input);
        QFETCH(QString, ip);
        QFETCH(quint16, port);

        QRegExp rx("--hblog-output-tcp:(.+):(\\d+)");
        rx.indexIn( input );
        QString ipFound = rx.cap( 1 );
        quint16 portFound = rx.cap( 2 ).toInt();

        QCOMPARE( ipFound, ip );
        QCOMPARE( portFound, port );
    }
};

QTEST_APPLESS_MAIN(TestParser)
#include "test_Parser.moc"
