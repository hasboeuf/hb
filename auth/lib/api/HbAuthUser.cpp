// Qt
#include <QtCore/QJsonObject>
// Hb
#include <HbLogService.h>
// Local
#include <api/HbAuthUser.h>

using namespace hb::auth;

QString HbAuthUser::toString() const {
    return QString("%1\nemail=%2\nverified=%3\nfirstname=%4\nlastname=%5\ngender=%6\nlocale=%7\nlink=%8\npicture=%"
                   "9\ntimezone=%10")
        .arg(HbAuthObject::toString())
        .arg(mEmail)
        .arg(mVerified)
        .arg(mFirstName)
        .arg(mLastName)
        .arg(mGender)
        .arg(mLocale)
        .arg(mLink)
        .arg(mPicture)
        .arg(mTimezone);
}

QString HbAuthUser::firstName() const {
    return mFirstName;
}

QString HbAuthUser::lastName() const {
    return mLastName;
}

QString HbAuthUser::link() const {
    return mLink;
}

QString HbAuthUser::email() const {
    return mEmail;
}

QString HbAuthUser::gender() const {
    return mGender;
}

QString HbAuthUser::locale() const {
    return mLocale;
}

bool HbAuthUser::isVerified() const {
    return mVerified;
}

QString HbAuthUser::picture() const {
    return mPicture;
}

void HbAuthUser::setFirstName(const QString& first_name) {
    mFirstName = first_name;
}
void HbAuthUser::setLastName(const QString& last_name) {
    mLastName = last_name;
}
void HbAuthUser::setLink(const QString& link) {
    mLink = link;
}
void HbAuthUser::setEmail(const QString& email) {
    mEmail = email;
}
void HbAuthUser::setGender(const QString& gender) {
    mGender = gender;
}
void HbAuthUser::setLocale(const QString& locale) {
    mLocale = locale;
}
void HbAuthUser::setVerified(bool verified) {
    mVerified = verified;
}
void HbAuthUser::setPicture(const QString& picture) {
    mPicture = picture;
}

void HbAuthUser::setTimezone(qint8 timezone) {
    mTimezone = timezone;
}
