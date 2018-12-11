/****************************************************************************
** Copyright (C) 2012-2015 Adrien Gavignet (hasboeuf)
** Contact: adrien.gavignet@gmail.com
**
** This file is part of the Hb module. Provided "AS IS", WITHOUT WARRANTIES
** OR CONDITIONS OF ANY KIND, either express or implied.
****************************************************************************/

#ifndef HBGOOGLEUSER_H
#define HBGOOGLEUSER_H

// Qt
#include <QtCore/QJsonDocument>
#include <QtCore/QString>
// Local
#include <HbLink.h>
#include <google/api/HbGoogleObject.h>

namespace hb {
namespace link {
/*!
 * HbGoogleUser describes a Google user object.
 */
class HB_LINK_DECL HbGoogleUser : public HbGoogleObject {
public:
    HbGoogleUser();
    virtual ~HbGoogleUser() = default;

    virtual void load(const QJsonDocument& doc) override;

    virtual QString toString() const override;

    virtual const QString& firstName() const;
    virtual const QString& lastName() const;
    virtual const QString& link() const;
    virtual const QString& email() const;
    virtual const QString& gender() const;
    virtual const QString& locale() const;
    virtual bool isVerified() const;
    virtual const QString& picture() const;

    virtual void setFirstName(const QString& first_name);
    virtual void setLastName(const QString& last_name);
    virtual void setLink(const QString& link);
    virtual void setEmail(const QString& email);
    virtual void setGender(const QString& gender);
    virtual void setLocale(const QString& locale);
    virtual void setVerified(bool verified);
    virtual void setPicture(const QString& picture);

protected:
    QString mFirstName;
    QString mLastName;
    QString mLink;
    QString mEmail;
    QString mGender;
    QString mLocale;
    bool mVerified;
    QString mPicture;
};
} // namespace link
} // namespace hb

using hb::link::HbGoogleUser;

#endif // HBGOOGLEUSER_H
