#ifndef HBSERVICEAUTHSERVERCONFIG_H
#define HBSERVICEAUTHSERVERCONFIG_H

/*! \file HbServiceAuthServerConfig.h */

// Qt
// Hb
#include <config/HbO2ServerConfig.h>
// Local
#include <HbNetwork.h>
#include <config/service/auth/HbServiceAuthConfig.h>

namespace hb {
namespace network {

class HB_NETWORK_DECL HbServiceAuthServerConfig : public HbServiceAuthConfig {
public:
    HbServiceAuthServerConfig();
    HbServiceAuthServerConfig(const HbServiceAuthServerConfig& config);
    virtual ~HbServiceAuthServerConfig() = default;
    virtual HbServiceAuthServerConfig& operator=(const HbServiceAuthServerConfig& config);

    virtual bool isValid() const;

    void enableFacebookAuth(const hb::link::HbO2ServerConfig& config);
    const hb::link::HbO2ServerConfig& facebookAuthConfig() const;

    void enableGoogleAuth(const hb::link::HbO2ServerConfig& config);
    const hb::link::HbO2ServerConfig& googleAuthConfig() const;

    virtual void setAuthMaxTries(quint16 max);
    virtual quint16 authMaxTries() const;

    virtual void setAuthTimeout(quint16 timeout);
    virtual quint16 authTimeout() const;

private:
    quint16 mAuthMaxTries;
    quint16 mAuthTimeout;
    hb::link::HbO2ServerConfig mFacebookAuthConfig;
    hb::link::HbO2ServerConfig mGoogleAuthConfig;
};
} // namespace network
} // namespace hb

using hb::network::HbServiceAuthServerConfig;

#endif // HBSERVICEAUTHSERVERCONFIG_H
