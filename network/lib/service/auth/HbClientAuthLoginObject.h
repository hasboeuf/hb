#ifndef HBCLIENTAUTHLOGINOBJECT_H
#define HBCLIENTAUTHLOGINOBJECT_H

/*! \file HbClientAuthLoginObject.h */

// Qt
// Hb
// Local
#include <service/auth/HbAuthService.h>

namespace hb {
namespace network {
/*!
 * TODOC
 */
class HB_NETWORK_DECL HbClientAuthLoginObject {
public:
    HbClientAuthLoginObject();
    virtual ~HbClientAuthLoginObject() = default;

    virtual void setStrategy(authstgy strategy);
    virtual void setSocketUid(networkuid socket_uid);

    virtual authstgy strategy() const;
    virtual networkuid socketUid() const;

protected:
    authstgy mStrategy;
    networkuid mSocketUid;
};
} // namespace network
} // namespace hb

using hb::network::HbClientAuthLoginObject;

#endif // HBCLIENTAUTHLOGINOBJECT_H
