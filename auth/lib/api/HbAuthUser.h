#ifndef HBAUTHUSER_H
#define HBAUTHUSER_H

// Qt
#include <QtCore/QJsonDocument>
#include <QtCore/QString>
// Local
#include <HbAuth.h>
#include <api/HbAuthObject.h>

namespace hb {
namespace auth {
/*!
 * HbAuthUser describes a auth user object.
 */
class HB_AUTH_DECL HbAuthUser : public HbAuthObject {
public:
    HbAuthUser() = default;
    virtual ~HbAuthUser() = default;

    QString toString() const override;

    QString firstName() const;
    QString lastName() const;
    QString link() const;
    QString email() const;
    QString gender() const;
    QString locale() const;
    bool isVerified() const;
    QString picture() const;
    qint8 timezone() const;

    void setFirstName(const QString& firstName);
    void setLastName(const QString& lastName);
    void setLink(const QString& link);
    void setEmail(const QString& email);
    void setGender(const QString& gender);
    void setLocale(const QString& locale);
    void setVerified(bool verified);
    void setPicture(const QString& picture);
    void setTimezone(qint8 timezone);

protected:
    QString mFirstName;
    QString mLastName;
    QString mLink;
    QString mEmail;
    QString mGender;
    QString mLocale;
    bool mVerified = false;
    QString mPicture;
    qint8 mTimezone = -1;
};
} // namespace auth
} // namespace hb

#endif // HBAUTHUSER_H
