#include <core/HbScopedFunction.h>
#include <QtCore/QObject>
#include <QtTest>

using namespace hb::tools;

class TestScopedFunction : public QObject {
    Q_OBJECT

private slots:

    void testDestructor() {
        // Given a callback incrementing an integer
        // When associated scoped function object dies
        // Then callback is called

        int i = 0;

        HbScopedFunction::Callback callback = [&i]() { ++i; };

        QCOMPARE(i, 0);

        {
            HbScopedFunction scopedFunctionA(callback);
            HbScopedFunction scopedFunctionB(callback);
        }

        QCOMPARE(i, 2);
    }
};

QTEST_APPLESS_MAIN(TestScopedFunction)
#include "test_HbScopedFunction.moc"
