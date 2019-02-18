#ifndef HBFACEBOOKUSER_H
#define HBFACEBOOKUSER_H

/*! \file HbFacebookUser.h */

// Qt
#include <QtCore/QJsonDocument>
#include <QtCore/QString>
// Local
#include <HbLink.h>
#include <facebook/api/HbFacebookObject.h>

namespace hb {
namespace link {
/*!
 * HbFacebookUser describes a Facebook user object.
 */
class HB_LINK_DECL HbFacebookUser : public HbFacebookObject {
public:
    HbFacebookUser();
    virtual ~HbFacebookUser() = default;

    virtual void load(const QJsonDocument& doc) override;

    virtual QString toString() const override;

    virtual const QString& firstName() const;
    virtual const QString& lastName() const;
    virtual const QString& link() const;
    virtual const QString& email() const;
    virtual const QString& gender() const;
    virtual const QString& locale() const;
    virtual bool isVerified() const;
    virtual qint8 timezone() const;

    virtual void setFirstName(const QString& first_name);
    virtual void setLastName(const QString& last_name);
    virtual void setLink(const QString& link);
    virtual void setEmail(const QString& email);
    virtual void setGender(const QString& gender);
    virtual void setLocale(const QString& locale);
    virtual void setVerified(bool verified);
    virtual void setTimezone(qint8 timezone);

protected:
    QString mFirstName;
    QString mLastName;
    QString mLink;
    QString mEmail;
    QString mGender;
    QString mLocale;
    bool mVerified;
    qint8 mTimezone;
};
} // namespace link
} // namespace hb

using hb::link::HbFacebookUser;

#endif // HBFACEBOOKUSER_H
