#include <QtTest>
#include <QtCore/QObject>
#include <core/HbUid.h>

using namespace hb::tools;

static const int CLASS_USER_A = CLASS_USER + 1;
static const int CLASS_USER_B = CLASS_USER + 2;

class ClassA: public HbUid< CLASS_USER_A > {};
class ClassB: public HbUid< CLASS_USER_B > {};

class TestHbUid : public QObject {
    Q_OBJECT

private slots:

    void init() {
        HbUidGenerator< CLASS_USER_A >::get()->reset();
        HbUidGenerator< CLASS_USER_B >::get()->reset();
    }

    void testUidStartsAtOne() {
        ClassA a;
        QCOMPARE( a.uid(), 1 );
    }

    void testUidBelongings() {
        ClassA a1, a2, a3;
        ClassB b1, b2, b3;

        QCOMPARE( a1.uid(), 1);
        QCOMPARE( a2.uid(), 2);
        QCOMPARE( a3.uid(), 3);

        QCOMPARE( b1.uid(), 1);
        QCOMPARE( b2.uid(), 2);
        QCOMPARE( b3.uid(), 3);
    }

    void testUidRecycling() {
        ClassA a1;
        QCOMPARE( a1.uid(), 1);

        {
            ClassA a2;
            ClassA a3;
            QCOMPARE( a2.uid(), 2);
            QCOMPARE( a3.uid(), 3);
        }

        ClassA a4, a5;
        QCOMPARE( a4.uid(), 3); // a3 is recycled first
        QCOMPARE( a5.uid(), 2);
    }

    void testTakeUid() {
        ClassA* a1 = new ClassA;
        ClassA* a2 = new ClassA;

        QCOMPARE( a1->uid(), 1);
        QCOMPARE( a2->uid(), 2);

        a2->takeUid( a1 );

        QCOMPARE( a1->uid(), 1);
        QCOMPARE( a2->uid(), 1); // Breaking unicity, as expected.

        ClassA a3;
        QCOMPARE( a3.uid(), 2 ); // a2 has released 2

        delete a1; // Does not release uid=1
        ClassA a4;
        QCOMPARE( a4.uid(), 3 );

        delete a2; // Release 1
        ClassA a5;
        QCOMPARE( a5.uid(), 1);
    }
};

QTEST_APPLESS_MAIN(TestHbUid)
#include "test_HbUid.moc"
