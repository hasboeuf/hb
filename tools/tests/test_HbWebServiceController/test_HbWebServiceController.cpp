#include <mock/MockNetwork.h>
#include <network/HbWebServiceController.h>
#include <network/HbWebServiceJob.h>
#include <QtCore/QObject>
#include <QtTest>

using namespace hb::tools;

class TestHbWebServiceController : public QObject {
    Q_OBJECT

private slots:

    void testGet() {
        MockNetworkAccessManager nam;
        HbWebServiceController controller(&nam);

        nam.enqueue(new MockNetworkReply(RAW_CONTENT, MockNetworkReply::HTTP200));
        nam.enqueue(new MockNetworkReply(JSON_CONTENT, MockNetworkReply::HTTP200));

        HbWebServiceJob* job = controller.get(TEST_URL);
        job->waitForFinished();
        QCOMPARE(job->result().httpStatusCode(), 200);
    }

    void testRetries() {
        MockNetworkAccessManager nam;
        HbWebServiceController controller(&nam);

        nam.enqueue(new MockNetworkReply(RAW_CONTENT, MockNetworkReply::Timeout));
        nam.enqueue(new MockNetworkReply(RAW_CONTENT, MockNetworkReply::Timeout));
        nam.enqueue(new MockNetworkReply(RAW_CONTENT, MockNetworkReply::HTTP200));

        HbWebServiceJob* job = controller.get(TEST_URL, 2);
        job->waitForFinished();
        QCOMPARE(job->result().httpStatusCode(), 200);
        QCOMPARE(job->result().networkError(), QNetworkReply::NoError);
    }

    void testTimeout() {
        MockNetworkAccessManager nam;
        HbWebServiceController controller(&nam);

        nam.enqueue(new MockNetworkReply(RAW_CONTENT, MockNetworkReply::HTTP200));

        HbWebServiceJob* job = controller.get(TEST_URL, 0, 0);
        job->waitForFinished();

        QCOMPARE(job->result().httpStatusCode(), 0);
        QCOMPARE(job->result().networkError(), QNetworkReply::TimeoutError);
    }
};

QTEST_GUILESS_MAIN(TestHbWebServiceController)
#include "test_HbWebServiceController.moc"
