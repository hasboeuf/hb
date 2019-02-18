#ifndef HBO2CLIENTFACEBOOK_H
#define HBO2CLIENTFACEBOOK_H

/*! \file HbO2ClientFacebook.h */

// Qt
#include <QtCore/QObject>
#include <QtCore/QUrl>
// Local
#include <HbO2Client.h>

namespace hb {
namespace link {
/*!
 * HbO2ClientFacebook is the Facebook implementation of HbO2Client.
 */
class HB_LINK_DECL HbO2ClientFacebook : public HbO2Client {
    Q_OBJECT

public:
    HbO2ClientFacebook() = default;
    virtual ~HbO2ClientFacebook() = default;

protected:
    virtual const QUrl endPoint() const override;
    virtual const QHash<QString, QString> codeRequest() const override;
    virtual LinkStatus codeResponse(const QHash<QString, QString>& response) override;
};
} // namespace link
} // namespace hb

using hb::link::HbO2ClientFacebook;

#endif // HBO2CLIENTFACEBOOK_H
