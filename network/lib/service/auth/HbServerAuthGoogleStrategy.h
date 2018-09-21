/****************************************************************************
** Copyright (C) 2012-2015 Adrien Gavignet (hasboeuf)
** Contact: adrien.gavignet@gmail.com
**
** This file is part of the Hb module. Provided "AS IS", WITHOUT WARRANTIES
** OR CONDITIONS OF ANY KIND, either express or implied.
****************************************************************************/

#ifndef HBSERVERAUTHGOOGLESTRATEGY_H
#define HBSERVERAUTHGOOGLESTRATEGY_H

// Qt
#include <QtCore/QHash>
// Hb
#include <google/HbGoogleRequester.h>
// Local
#include <HbNetwork.h>
#include <contract/HbNetworkProtocol.h>
#include <contract/auth/HbAuthRequestContract.h> // Template.
#include <service/auth/HbServerOAuthStrategy.h>

namespace hb {
using namespace link;

namespace network {
/*!
 * TODOC
 */
class HB_NETWORK_DECL HbServerAuthGoogleStrategy : public HbServerOAuthStrategy {
    Q_OBJECT
public:
    HbServerAuthGoogleStrategy();
    virtual ~HbServerAuthGoogleStrategy() = default;

    virtual authstgy type() const final;
    virtual bool checkLogin(const HbAuthRequestContract* contract) override;

public slots:
    void onLinkSucceed();
    void onRequestCompleted(quint64 request_id, HbGoogleObject* object);

private:
    HbGoogleRequester mRequester;
};
} // namespace network
} // namespace hb

using hb::network::HbServerAuthGoogleStrategy;

#endif // HBSERVERAUTHGOOGLESTRATEGY_H
