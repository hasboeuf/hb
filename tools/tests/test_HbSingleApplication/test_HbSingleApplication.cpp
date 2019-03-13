#include <core/HbSingleApplication.h>
#include <QtCore/QObject>
#include <QtCore/QVariant>
#include <QtTest>

using namespace hb::tools;

class TestSingleApplication : public QObject {
    Q_OBJECT

private slots:

    void testMessaging() {
        // Given a SingleApplication running
        // When a second is started
        // Then connection is successful and messaging works
        HbSingleApplication firstApp;
        firstApp.setMessageHandlerFunction([](const QVariant& message) -> QVariant {
            Q_ASSERT(message.toString() == "hell");
            return 666;
        });
        QVERIFY(!firstApp.connectToExistingApplication());
        QVERIFY(firstApp.acquireApplication());

        HbSingleApplication secondApp;
        QVERIFY(secondApp.connectToExistingApplication());
        QCOMPARE(secondApp.sendToExistingApplication("hell").toInt(), 666);
    }

    void testSendTimeout() {
        // Given a SingleApplication running
        // When a second is instanciated
        // Then connection is successful but messaging does not work with tight timeout
        HbSingleApplication firstApp;
        firstApp.setMessageHandlerFunction([](const QVariant& message) -> QVariant {
            Q_ASSERT(message.toString() == "hell");
            return 666;
        });
        firstApp.acquireApplication();

        HbSingleApplication secondApp;
        secondApp.connectToExistingApplication();
        QCOMPARE(secondApp.sendToExistingApplication("hell", 0), QVariant());
    }
};

QTEST_GUILESS_MAIN(TestSingleApplication)
#include "test_HbSingleApplication.moc"
