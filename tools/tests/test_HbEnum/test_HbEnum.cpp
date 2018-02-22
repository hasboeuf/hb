#include <QtTest>
#include <QtCore/QObject>
#include <core/HbEnum.h>

using namespace hb::tools;

class TestHbEnum : public QObject {
    Q_OBJECT

public:
    enum MyEnum {
        Value1,
        Value2,
        Value3,
    };
    Q_ENUM(MyEnum)
    HB_ENUM(MyEnum)

private slots:

    void testToString() {

        QCOMPARE( MetaMyEnum::toString(), QStringList() << "Value1" << "Value2" << "Value3" );
        QCOMPARE( MetaMyEnum::toString( Value1 ), "Value1" );
        QCOMPARE( MetaMyEnum::toString( Value2 ), "Value2" );
        QCOMPARE( MetaMyEnum::toString( Value3 ), "Value3" );
        QCOMPARE( MetaMyEnum::toString( 0 ), "Value1" );
        QCOMPARE( MetaMyEnum::toString( 1 ), "Value2" );
        QCOMPARE( MetaMyEnum::toString( 2 ), "Value3" );
    }

    void testFromString() {
        QCOMPARE( MetaMyEnum::fromString( "Value1" ), Value1 );
        QCOMPARE( MetaMyEnum::fromString( "Value2" ), Value2 );
        QCOMPARE( MetaMyEnum::fromString( "Value3" ), Value3 );
    }
};

QTEST_APPLESS_MAIN(TestHbEnum)
#include "test_HbEnum.moc"
