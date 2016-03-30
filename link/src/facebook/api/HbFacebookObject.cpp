// Local
#include <facebook/api/HbFacebookObject.h>
#include <HbLinkConstant.h>

HbFacebookObject::HbFacebookObject()
{
    mType = OBJECT_NONE;
}

const QString HbFacebookObject::toString() const
{
    return QString( "%1=%2; %3=%4" )
            .arg( "type" )
            .arg( HbFacebookObject::MetaObjectType::toString( mType ) )
            .arg( FB_OBJECT_ID )
            .arg( mId );

}

void HbFacebookObject::setId( const QString & id )
{
    mId = id;
}

const QString & HbFacebookObject::id() const
{
    return mId;
}

HbFacebookObject::ObjectType HbFacebookObject::type() const
{
    return mType;
}
