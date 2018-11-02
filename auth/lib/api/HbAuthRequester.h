/****************************************************************************
** Copyright (C) 2012-2015 Adrien Gavignet (hasboeuf)
** Contact: adrien.gavignet@gmail.com
**
** This file is part of the Hb module. Provided "AS IS", WITHOUT WARRANTIES
** OR CONDITIONS OF ANY KIND, either express or implied.
****************************************************************************/

#ifndef HBAUTHREQUESTER_H
#define HBAUTHREQUESTER_H

// Qt
#include <QtCore/QObject>
#include <QtCore/QString>
// Hb
#include <network/HbWebServiceController.h>
// Local
#include <HbAuth.h>
#include <HbAuth2FlowConfig.h>
#include <api/HbAuthUser.h>

class QNetworkAccessManager;

namespace hb {
namespace auth {

class WebServiceJob;

/*!
 * HbAuthRequester is a Http requester dedicated to an auth api
 */
class HB_AUTH_DECL HbAuthRequester : public QObject {
    Q_OBJECT

    //! \todo hide HbHttpRequester signals.
public:
    HbAuthRequester(QNetworkAccessManager* networkAccessManager, QObject* parent = nullptr);
    virtual ~HbAuthRequester() = default;

    void setConfig(const HbAuth2FlowConfig& config);

    virtual void requestUser() = 0;

signals:
    void userRequestFinished(const HbAuthUser& user);

protected:
    tools::HbWebServiceJob* request(const QUrl& url, const QVariantMap& parameters);
    HbAuth2FlowConfig mConfig;

private:
    tools::HbWebServiceController mWebServiceController;
};
} // namespace auth
} // namespace hb

#endif // HBAUTHREQUESTER_H
