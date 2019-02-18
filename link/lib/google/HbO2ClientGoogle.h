#ifndef HBO2CLIENTGOOGLE_H
#define HBO2CLIENTGOOGLE_H

// Qt
#include <QtCore/QObject>
#include <QtCore/QUrl>
// Local
#include <HbO2Client.h>

namespace hb {
namespace link {
/*!
 * HbO2ClientGoogle is the Google implementation of HbO2Client.
 */
class HB_LINK_DECL HbO2ClientGoogle : public HbO2Client {
    Q_OBJECT

public:
    HbO2ClientGoogle();
    virtual ~HbO2ClientGoogle() = default;

protected:
    virtual const QUrl endPoint() const override;
    virtual const QHash<QString, QString> codeRequest() const override;
    virtual LinkStatus codeResponse(const QHash<QString, QString>& response) override;
};
} // namespace link
} // namespace hb

using hb::link::HbO2ClientGoogle;

#endif // HBO2CLIENTGOOGLE_H
