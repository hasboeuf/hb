#ifndef HBO2CLIENTCONFIG_H
#define HBO2CLIENTCONFIG_H

/*! \file HbO2ClientConfig.h */

// Qt
// Hb
#include <QtCore/QStringList>
// Local
#include <config/HbO2Config.h>

namespace hb {
namespace link {

class IHbLinkBrowserControls;

/*!
 * TODOC
 */
class HB_LINK_DECL HbO2ClientConfig : public HbO2Config {
public:
    HbO2ClientConfig();
    HbO2ClientConfig(const HbO2ClientConfig& config);
    virtual ~HbO2ClientConfig() = default;
    virtual HbO2ClientConfig& operator=(const HbO2ClientConfig& config);

    virtual bool isValid() const;

    virtual bool read(QDataStream& stream);
    virtual bool write(QDataStream& stream) const;

    virtual void setLocalPort(quint16 local_port);
    virtual quint16 localPort() const;

    virtual void addScope(const QString& permission);
    virtual void setScopes(const QStringList& permissions);
    virtual const QStringList& scopes() const;
    virtual QString scopesStr() const;

    virtual void setScopeSeparator(const QString& separator);

    void setBrowserControls(IHbLinkBrowserControls* browser_controls);
    IHbLinkBrowserControls* browserControls();

private:
    QStringList mScopes;
    QString mScopesSeparator;
    quint16 mLocalPort;
    IHbLinkBrowserControls* mBrowserControls; // Not serialized.
};
} // namespace link
} // namespace hb

using hb::link::HbO2ClientConfig;

#endif // HBO2CLIENTCONFIG_H
