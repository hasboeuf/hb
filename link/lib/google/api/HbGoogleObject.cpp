// Local
#include <HbLinkConstant.h>
#include <google/api/HbGoogleObject.h>

HbGoogleObject::HbGoogleObject() {
    mType = OBJECT_NONE;
}

QString HbGoogleObject::toString() const {
    return QString("%1=%2; %3=%4")
        .arg("type")
        .arg(HbGoogleObject::MetaObjectType::toString(mType))
        .arg(GL_OBJECT_ID)
        .arg(mId);
}

void HbGoogleObject::setId(const QString& id) {
    mId = id;
}

const QString& HbGoogleObject::id() const {
    return mId;
}

HbGoogleObject::ObjectType HbGoogleObject::type() const {
    return mType;
}
