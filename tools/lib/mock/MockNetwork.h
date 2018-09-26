#include <QtCore/QQueue>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>

static const QUrl TEST_URL("https://api.google.com");
static const QByteArray RAW_CONTENT = "OK";
static const QByteArray JSON_CONTENT = R"json(
{
    "age": 15
}
)json";

class MockNetworkReply : public QNetworkReply {
    Q_OBJECT
public:
    enum Error {
        HTTP200,
        HTTP301,
        HTTP302,
        HTTP400,
        HTTP401,
        HTTP403,
        HTTP404,
        HTTP405,
        HTTP407,
        HTTP409,
        HTTP410,
        HTTP418,
        HTTP500,
        HTTP501,
        HTTP503,
        ConnectionRefused,
        Timeout,
    };
    Q_ENUM(Error)

    MockNetworkReply(const QByteArray data = QByteArray(), Error code = Error::HTTP200, QObject* parent = nullptr);
    void abort() override;
    void start();

protected:
    qint64 readData(char* data, qint64 maxLen) override;
    qint64 writeData(const char* data, qint64 maxSize) override;
    qint64 bytesAvailable() const override;

private:
    void onFinished();
    QByteArray mData;
    qint64 mDataIndex = 0;
    QNetworkReply::NetworkError mNetworkError;
};

class MockNetworkAccessManager : public QNetworkAccessManager {
public:
    void enqueue(MockNetworkReply* reply);

protected:
    QNetworkReply*
    createRequest(Operation operation, const QNetworkRequest& request, QIODevice* outgoingData = nullptr) override;

private:
    QQueue<MockNetworkReply*> mReplies;
};
