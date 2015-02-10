// Qt
#include <QtCore/QUrl>
#include <QtCore/QUrlQuery>
#include <QtCore/QJsonObject>
// Hb
#include <HbLogService.h>
#include <core/HbDictionaryHelper.h>
// Local
#include <facebook/HbFacebookRequester.h>
#include <facebook/HbO2ServerFacebook.h>
#include <facebook/api/HbFacebookUser.h>

using namespace hb::link;

HbFacebookRequester::HbFacebookRequester() :
    HbLinkRequester()
{

    connect( this, &HbLinkRequester::requestFinished, this, &HbFacebookRequester::onRequestFinished );
    connect( this, &HbLinkRequester::requestError,    this, &HbFacebookRequester::onRequestError );
}

bool HbFacebookRequester::requestUser( HbO2ServerFacebook * auth )
{
    if( !auth || ( auth->linkStatus() != HbO2::LINKED ) )
    {
        HbError( "Auth null or unlinked." );
        return false;
    }

    // Test
    QUrl url( "https://graph.facebook.com/me" );
    QUrlQuery request( url );

    QHash< QString, QString > params;
    params.insert( FB_TOKEN, auth->token() );

    request.setQueryItems( HbDictionaryHelper::toPairList< QString, QString >( params ) );
    url.setQuery( request );

    qint64 id = processRequest( url );
    if( id < 0 )
    {
        return false;
    }

    mRequestTypes.insert( id, HbFacebookObject::OBJECT_USER );
    HbInfo( "Request %lld is sent (%s).", id, HbLatin1( url.toString() ) );

    return true;
}

void HbFacebookRequester::onRequestFinished( quint64 request_id, const QJsonDocument & doc )
{

    HbFacebookObject::ObjectType type = HbFacebookObject::OBJECT_NONE;

    if( mRequestTypes.contains( request_id ) )
    {
        type = mRequestTypes.take( request_id );
    }

    HbInfo( "Request (%lld) of type %s completed.",
            request_id,
            HbLatin1( HbFacebookObject::MetaObjectType::toString( type ) ) );


    if( type == HbFacebookObject::OBJECT_USER )
    {
        HbFacebookUser * user = new HbFacebookUser();
        user->load( doc );
        emit requestCompleted( user );
    }
    else
    {
        HbError( "Object creation failed, bad type." );
        emit requestCompleted( nullptr );
    }
}

void HbFacebookRequester::onRequestError( quint64 request_id, const QString & error )
{
    HbFacebookObject::ObjectType type = HbFacebookObject::OBJECT_NONE;

    if( mRequestTypes.contains( request_id ) )
    {
        type = mRequestTypes.take( request_id );
    }

    HbError( "Request (%lld) of type %s failed (%s).",
             request_id,
             HbLatin1( HbFacebookObject::MetaObjectType::toString( type ) ),
             HbLatin1( error ) );

    emit requestCompleted( nullptr );
}
