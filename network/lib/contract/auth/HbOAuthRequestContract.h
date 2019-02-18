#ifndef HBOAUTHREQUESTCONTRACT_H
#define HBOAUTHREQUESTCONTRACT_H

// Qt
#include <QtCore/QObject>
#include <QtCore/QSet>
// Hb
#include <HbGlobal.h>
// Local
#include <HbNetwork.h>
#include <contract/auth/HbAuthRequestContract.h>

namespace hb {
namespace network {
/*!
 * TODOC
 */
class HB_NETWORK_DECL HbOAuthRequestContract : public HbAuthRequestContract {
public:
    HbOAuthRequestContract();
    virtual ~HbOAuthRequestContract() = default;
    HbOAuthRequestContract(const HbOAuthRequestContract& source);
    HbOAuthRequestContract& operator=(const HbOAuthRequestContract& source);

    virtual HbOAuthRequestContract* create() const override;

    virtual bool read(QDataStream& stream) override;
    virtual bool write(QDataStream& stream) const override;

    const QString& code() const;
    const QString& redirectUri() const;

    void setCode(const QString& code);
    void setRedirectUri(const QString& redirect_uri);

protected:
    QString mCode;
    QString mRedirectUri;
};
} // namespace network
} // namespace hb

using hb::network::HbOAuthRequestContract;

#endif // HBOAUTHREQUESTCONTRACT_H
