#ifndef HBNETWORKUSERINFO_H
#define HBNETWORKUSERINFO_H

/*! \file HbNetworkUserInfo.h */

// Qt
#include <QtCore/QDataStream>
#include <QtCore/QSharedPointer>
#include <QtCore/QString>
// Hb
// Local
#include <HbNetwork.h>

namespace hb {
namespace network {

/*!
 * TODOC
 */
class HB_NETWORK_DECL HbNetworkUserInfo {
    friend QDataStream& operator<<(QDataStream& stream, const HbNetworkUserInfo& header);
    friend QDataStream& operator>>(QDataStream& stream, HbNetworkUserInfo& header);

public:
    enum Gender : netwint { GENDER_NONE = 0, GENDER_MALE, GENDER_FEMALE };

    HbNetworkUserInfo();
    virtual ~HbNetworkUserInfo() = default;
    HbNetworkUserInfo(const HbNetworkUserInfo& source);
    HbNetworkUserInfo& operator=(const HbNetworkUserInfo& source);

    QString id() const;
    authstgy type() const;
    QString email() const;
    QString nickname() const;
    QString firstName() const;
    QString lastName() const;
    quint8 age() const;
    Gender gender() const;
    const QString& picture() const;

    void setId(const QString& id);
    void setType(authstgy type);
    void setEmail(const QString& email);
    void setNickname(const QString& nickname);
    void setFirstName(const QString& first_name);
    void setLastName(const QString& last_name);
    void setAge(quint8 age);
    void setGender(Gender gender);
    void setPicture(const QString& picture);

private:
    QString mId;
    authstgy mType;
    QString mEmail;
    QString mNickname;
    QString mFirstName;
    QString mLastName;
    quint8 mAge;
    Gender mGender;
    QString mPicture;
};

QDataStream& operator<<(QDataStream& stream, const HbNetworkUserInfo& header);
QDataStream& operator>>(QDataStream& stream, HbNetworkUserInfo& header);

typedef QSharedPointer<const HbNetworkUserInfo> ShConstHbNetworkUserInfo;
typedef QSharedPointer<HbNetworkUserInfo> ShHbNetworkUserInfo;

} // namespace network
} // namespace hb

Q_DECLARE_METATYPE(hb::network::HbNetworkUserInfo)

using hb::network::HbNetworkUserInfo;

#endif // HBNETWORKUSERINFO_H
