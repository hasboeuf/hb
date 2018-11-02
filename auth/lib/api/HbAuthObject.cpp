// Local
#include <api/HbAuthObject.h>

using namespace hb::auth;

bool HbAuthObject::isValid() const {
    return mErrorCode == NONE;
}

void HbAuthObject::setError(Error errorCode, QString errorMessage) {
    mErrorCode = errorCode;
    mErrorMessage = errorMessage;
}

int HbAuthObject::errorCode() const {
    return mErrorCode;
}

QString HbAuthObject::errorMessage() const {
    return mErrorMessage;
}

QString HbAuthObject::toString() const {
    return QString("valid=%1\nerrorcode=%2\nerrormessage=%3\nsource=%4\nid=%5")
        .arg(isValid())
        .arg(mErrorCode)
        .arg(mErrorMessage)
        .arg(mSource)
        .arg(mId);
}

void HbAuthObject::setId(const QString& id) {
    mId = id;
}

QString HbAuthObject::id() const {
    return mId;
}

void HbAuthObject::setSource(Source source) {
    mSource = source;
}

HbAuthObject::Source HbAuthObject::source() const {
    return mSource;
}
