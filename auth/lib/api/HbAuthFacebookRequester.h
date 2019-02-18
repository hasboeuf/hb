#ifndef HBAUTHFACEBOOKREQUESTER_H
#define HBAUTHFACEBOOKREQUESTER_H

// Qt
#include <QtCore/QObject>
#include <QtCore/QString>
// Hb
// Local
#include <HbAuth.h>
#include <api/HbAuthRequester.h>

class QNetworkAccessManager;

namespace hb {
namespace auth {

/*!
 * HbAuthFacebookRequester is a Http requester dedicated to Facebook auth api
 */
class HB_AUTH_DECL HbAuthFacebookRequester : public HbAuthRequester {
public:
    HbAuthFacebookRequester(QNetworkAccessManager* networkAccessManager, QObject* parent = nullptr);
    virtual ~HbAuthFacebookRequester() = default;

    void requestUser() override;

private:
    void onRequestUserFinished(const tools::HbWebServiceResult& result);
};
} // namespace auth
} // namespace hb

#endif // HBAUTHFACEBOOKREQUESTER_H
