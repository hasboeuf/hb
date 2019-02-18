#ifndef HBSERVICEAUTHCLIENTCONFIG_H
#define HBSERVICEAUTHCLIENTCONFIG_H

/*! \file HbServiceAuthClientConfig.h */

// Qt
// Hb
#include <config/HbO2ClientConfig.h>
// Local
#include <HbNetwork.h>
#include <config/service/auth/HbServiceAuthConfig.h>

namespace hb {
namespace network {
class HB_NETWORK_DECL HbServiceAuthClientConfig : public HbServiceAuthConfig {
public:
    HbServiceAuthClientConfig();
    HbServiceAuthClientConfig(const HbServiceAuthClientConfig& config);
    virtual ~HbServiceAuthClientConfig() = default;
    virtual HbServiceAuthClientConfig& operator=(const HbServiceAuthClientConfig& config);

    virtual bool isValid() const;

    void enableFacebookAuth(const hb::link::HbO2ClientConfig& config);
    const hb::link::HbO2ClientConfig& facebookAuthConfig() const;

    void enableGoogleAuth(const hb::link::HbO2ClientConfig& config);
    const hb::link::HbO2ClientConfig& googleAuthConfig() const;

protected:
private:
    hb::link::HbO2ClientConfig mFacebookAuthConfig;
    hb::link::HbO2ClientConfig mGoogleAuthConfig;
};
} // namespace network
} // namespace hb

using hb::network::HbServiceAuthClientConfig;

#endif // HBSERVICEAUTHCLIENTCONFIG_H
