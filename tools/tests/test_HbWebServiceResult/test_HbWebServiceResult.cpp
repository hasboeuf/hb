#include <mock/MockNetwork.h>
#include <network/HbWebServiceJob.h>
#include <QtCore/QByteArray>
#include <QtCore/QObject>
#include <QtTest>

using namespace hb::tools;

class TestHbWebServiceResult : public QObject {
    Q_OBJECT

private slots:
    void testRawContent() {
        HbWebServiceResult result;
        result.mContent = RAW_CONTENT;

        QCOMPARE(result.rawContent(), RAW_CONTENT);
    }

    void testJsonContent() {
        HbWebServiceResult result;
        result.mContent = JSON_CONTENT;

        QCOMPARE(result.jsonContent().toJson(), QJsonDocument::fromJson(JSON_CONTENT).toJson());
    }
};

QTEST_GUILESS_MAIN(TestHbWebServiceResult)
#include "test_HbWebServiceResult.moc"
