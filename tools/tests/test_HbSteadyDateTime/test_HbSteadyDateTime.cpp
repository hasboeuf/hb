#include <QtCore/QObject>
#include <QtTest>

#include <core/HbSteadyDateTime.h>

using namespace hb::tools;

class TestHbSteadyDateTime : public QObject {
    Q_OBJECT

private slots:

    void testNow() {
        // Given one steady datetime
        // When created
        // Then QDateTime::toMSecsSinceEpoch() is the same with a margin of 2 ms

        auto qtDateTime = QDateTime::currentDateTime();
        auto steadyDateTime = HbSteadyDateTime::now();

        QVERIFY(qtDateTime.toMSecsSinceEpoch() * 1000 * 1000 < steadyDateTime.toNsSinceEpoch());
        QVERIFY(qtDateTime.toMSecsSinceEpoch() * 1000 * 1000 > steadyDateTime.toNsSinceEpoch() - 2000 * 1000);
    }

    void testFromDateTime() {
        // Given one steady datetime
        // When created from a QDateTime
        // Then dateTime() is consistent

        auto qtDateTime = QDateTime::currentDateTime();
        auto steadyDateTime = HbSteadyDateTime::fromDateTime(qtDateTime, 666);

        QCOMPARE(steadyDateTime.datetime(), qtDateTime);
        QCOMPARE(steadyDateTime.steady(), 666u);
    }

    void testFromString() {
        // Given one steady datetime
        // When created from a string
        // Then dateTime() is correct and HbSteadyDateTime::toString() is consistent

        QString format = "yyyy/MM/dd hh:mm:ss:zzz.uuuuuu";
        QString value = "2018/01/25 05:35:15:666.uuuuuu";
        auto qtDateTime = QDateTime::fromString(value, format);

        value.replace("uuuuuu", "012340");
        auto steadyDateTime = HbSteadyDateTime::fromString(value, format);

        QCOMPARE(steadyDateTime.datetime(), qtDateTime);
        QCOMPARE(steadyDateTime.steady(), 12340u);
        QCOMPARE(steadyDateTime.toString(format), value);
    }

    void testFromNsSinceEpoch() {
        // Given one steady datetime
        // When created from nanoseconds
        // Then datetime() is correct and HbSteadyDateTime::toNsSinceEpoch() is consistent

        auto nsSinceEpoch = QDateTime::currentMSecsSinceEpoch() * 1000 * 1000;
        auto a = HbSteadyDateTime::fromNsSinceEpoch(nsSinceEpoch);

        QCOMPARE(a.toNsSinceEpoch(), nsSinceEpoch);
    }

    void testSteadyness() {
        // Given two steady datetimes A, B
        // When created in a row
        // Then A != B

        auto a = HbSteadyDateTime::now();
        auto b = HbSteadyDateTime::now();

        QVERIFY(a.toNsSinceEpoch() != b.toNsSinceEpoch());
    }
};

QTEST_APPLESS_MAIN(TestHbSteadyDateTime)
#include "test_HbSteadyDateTime.moc"
