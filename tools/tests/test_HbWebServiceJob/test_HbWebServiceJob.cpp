#include <mock/MockNetwork.h>
#include <network/HbWebServiceController.h>
#include <network/HbWebServiceJob.h>
#include <QtCore/QObject>
#include <QtTest>

using namespace hb::tools;

class TestHbWebServiceJob : public QObject {
    Q_OBJECT

private slots:

    void testCancel() {
        MockNetworkAccessManager nam;
        HbWebServiceController controller(&nam);

        nam.enqueue(new MockNetworkReply(RAW_CONTENT, MockNetworkReply::HTTP200));

        auto job = controller.get(TEST_URL);
        job->cancel();
        job->waitForFinished();

        QCOMPARE(job->result().httpStatusCode(), 0);
        QCOMPARE(job->result().networkError(), QNetworkReply::OperationCanceledError);
    }

    void testWaitForFinishedSuccess() {
        MockNetworkAccessManager nam;
        HbWebServiceController controller(&nam);

        nam.enqueue(new MockNetworkReply(RAW_CONTENT, MockNetworkReply::HTTP200));

        auto job = controller.get(TEST_URL);
        QVERIFY(job->waitForFinished());

        QCOMPARE(job->result().httpStatusCode(), 200);
        QCOMPARE(job->result().networkError(), QNetworkReply::NoError);
    }

    void testWaitForFinishedFailure() {
        MockNetworkAccessManager nam;
        HbWebServiceController controller(&nam);

        nam.enqueue(new MockNetworkReply(RAW_CONTENT, MockNetworkReply::HTTP200));

        auto job = controller.get(TEST_URL);
        QVERIFY(!job->waitForFinished(0));

        QCOMPARE(job->result().httpStatusCode(), 0);
        QCOMPARE(job->result().networkError(), QNetworkReply::OperationCanceledError);
    }
};

QTEST_GUILESS_MAIN(TestHbWebServiceJob)
#include "test_HbWebServiceJob.moc"
