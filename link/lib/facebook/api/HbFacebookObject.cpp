// Local
#include <HbLinkConstant.h>
#include <facebook/api/HbFacebookObject.h>

HbFacebookObject::HbFacebookObject() {
    mType = OBJECT_NONE;
}

QString HbFacebookObject::toString() const {
    return QString("%1=%2; %3=%4")
        .arg("type")
        .arg(HbFacebookObject::MetaObjectType::toString(mType))
        .arg(FB_OBJECT_ID)
        .arg(mId);
}

void HbFacebookObject::setId(const QString& id) {
    mId = id;
}

const QString& HbFacebookObject::id() const {
    return mId;
}

HbFacebookObject::ObjectType HbFacebookObject::type() const {
    return mType;
}
