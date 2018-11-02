/****************************************************************************
** Copyright (C) 2012-2015 Adrien Gavignet (hasboeuf)
** Contact: adrien.gavignet@gmail.com
**
** This file is part of the Hb module. Provided "AS IS", WITHOUT WARRANTIES
** OR CONDITIONS OF ANY KIND, either express or implied.
****************************************************************************/

#ifndef HBAUTHGOOGLEREQUESTER_H
#define HBAUTHGOOGLEREQUESTER_H

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
 * HbAuthGoogleRequester is a Http requester dedicated to Google auth api
 */
class HB_AUTH_DECL HbAuthGoogleRequester : public HbAuthRequester {
public:
    HbAuthGoogleRequester(QNetworkAccessManager* networkAccessManager, QObject* parent = nullptr);
    virtual ~HbAuthGoogleRequester() = default;

    void requestUser() override;

private:
    void onRequestUserFinished(const tools::HbWebServiceResult& result);
};
} // namespace auth
} // namespace hb

#endif // HBAUTHGOOGLEREQUESTER_H
