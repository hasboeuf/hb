#ifndef HBO2SERVERCONFIG_H
#define HBO2SERVERCONFIG_H

/*! \file HbO2ServerConfig.h */

// Qt
// Hb
// Local
#include <config/HbO2Config.h>

namespace hb {
namespace link {

/*!
 * TODOC
 */
class HB_LINK_DECL HbO2ServerConfig : public HbO2Config {
public:
    HbO2ServerConfig() = default;
    HbO2ServerConfig(const HbO2ServerConfig& config);
    virtual ~HbO2ServerConfig() = default;
    virtual HbO2ServerConfig& operator=(const HbO2ServerConfig& config);

    virtual bool isValid() const;

    virtual bool read(QDataStream& stream);
    virtual bool write(QDataStream& stream) const;

    virtual void setClientSecret(const QString& client_secret);
    virtual const QString& clientSecret() const;

private:
    QString mClientSecret;
};
} // namespace link
} // namespace hb

using hb::link::HbO2ServerConfig;

#endif // HBO2SERVERCONFIG_H
