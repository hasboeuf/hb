#ifndef HBO2CONFIG_H
#define HBO2CONFIG_H

/*! \file HbO2Config.h */

// Qt
#include <QtCore/QDataStream>
#include <QtCore/QString>
// Hb
// Local
#include <HbLink.h>

namespace hb {
namespace link {

/*!
 * TODOC
 */
class HB_LINK_DECL HbO2Config {
    friend QDataStream& operator<<(QDataStream& stream, const HbO2Config& config);
    friend QDataStream& operator>>(QDataStream& stream, HbO2Config& config);

public:
    HbO2Config() = default;
    HbO2Config(const HbO2Config& config);
    virtual ~HbO2Config() = default;
    virtual HbO2Config& operator=(const HbO2Config& config);

    virtual bool isValid() const;

    virtual bool read(QDataStream& stream) = 0;
    virtual bool write(QDataStream& stream) const = 0;

    QString clientId() const;
    void setClientId(const QString& client_id);

private:
    QString mClientId;
};

QDataStream& operator<<(QDataStream& stream, const HbO2Config& config);
QDataStream& operator>>(QDataStream& stream, HbO2Config& config);
} // namespace link
} // namespace hb

using hb::link::HbO2Config;

#endif // HBO2CONFIG_H
