#include <QtTest>
#include <QtCore/QObject>
#include <core/HbSettings.h>

using namespace hb::tools;

class TestHbSettings : public QObject {
    Q_OBJECT

private slots:

    void testIsValid() {
        HbSettings invalidSettings;
        QVERIFY(!invalidSettings.isValid());

        QCoreApplication::setOrganizationName("hbtesting");

        HbSettings validSettings;
        QVERIFY(validSettings.isValid());
    }

    void testWriteReadRemove() {
        QCoreApplication::setOrganizationName("hbtesting");

        HbSettings settings;
        QVERIFY(settings.write("key", "value"));
        QCOMPARE(settings.read("key"), QVariant("value"));

        settings.remove("key");
        QCOMPARE(settings.read("key"), QVariant());
    }
};

QTEST_APPLESS_MAIN(TestHbSettings)
#include "test_HbSettings.moc"
