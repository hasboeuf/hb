#ifndef HBNETWORKEXCHANGES_H
#define HBNETWORKEXCHANGES_H

/*! \file HbNetworkExchanges.h */

// Qt
#include <QtCore/QIODevice>
// Hb
#include <HbGlobal.h>
// Local
#include <HbNetwork.h>
#include <contract/HbNetworkContract.h>

namespace hb {
namespace network {
/*!
 * TODOC
 */
class HB_NETWORK_DECL HbNetworkExchanges {
    friend class HbNetworkConfig;

protected:
    HbNetworkExchanges() = default;
    virtual ~HbNetworkExchanges();
    HbNetworkExchanges& operator=(const HbNetworkExchanges& source);

public:
    template <typename T> inline bool plug() {
        T* reference = q_check_ptr(new T());
        HbNetworkContract* contract = dynamic_cast<HbNetworkContract*>(reference);
        if (!contract) {
            return false;
        }

        return add(reference);
    }

    template <typename T> inline bool unplug() {
        T* reference = q_check_ptr(new T());
        HbNetworkContract* contract = dynamic_cast<HbNetworkContract*>(reference);
        if (!contract) {
            return false;
        }
        return remove(reference);
    }

    bool registered(serviceuid service, codeuid code) const;
    HbNetworkContract* contract(const HbNetworkHeader& header) const;

private:
    bool add(HbNetworkContract* contract);
    bool remove(HbNetworkContract* contract);

    typedef QHash<codeuid, HbNetworkContract*> Contracts;
    QHash<serviceuid, Contracts> mContracts;
};
} // namespace network
} // namespace hb

using hb::network::HbNetworkExchanges;

#endif // HBNETWORKEXCHANGES_H
