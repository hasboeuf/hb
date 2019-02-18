#ifndef HBWEBSERVICECONTROLLER_H
#define HBWEBSERVICECONTROLLER_H

/*! \file HbWebServiceController.h */

// Qt
#include <QtCore/QJsonDocument>
#include <QtCore/QScopedPointer>
// Local
#include <HbTools.h>
#include <network/HbWebServiceResult.h>

class QNetworkAccessManager;

namespace hb {
namespace tools {
class HbWebServiceJob;
/*!
 * WebService controller able to order HTTP request and return its represention through HbWebServiceJob
 */
class HB_TOOLS_DECL HbWebServiceController : public QObject {
    Q_OBJECT

public:
    HbWebServiceController(QNetworkAccessManager* networkAccessManager, QObject* parent = nullptr);

    HbWebServiceJob* get(const QUrl& url, int retries = 0, int timeout = -1);

private:
    void call(std::function<QNetworkReply*()> webServiceCall, HbWebServiceJob* webServiceJob, int retries, int timeout);
    void onCallFinished(HbWebServiceJob* webServiceJob,
                        QNetworkReply* networkReply,
                        std::function<QNetworkReply*()> webServiceCall,
                        int retries,
                        int timeout);
    HbWebServiceResult resultForReply(QNetworkReply* reply);

    QNetworkAccessManager* mNetworkAccessManager;
};
} // namespace tools
} // namespace hb

#endif // HBWEBSERVICECONTROLLER_H
