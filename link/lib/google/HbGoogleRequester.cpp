// Qt
#include <QtCore/QUrl>
#include <QtCore/QUrlQuery>
#include <QtCore/QJsonObject>
// Hb
#include <HbLogService.h>
#include <core/HbDictionaryHelper.h>
// Local
#include <google/HbGoogleRequester.h>
#include <google/HbO2ServerGoogle.h>
#include <google/api/HbGoogleUser.h>

using namespace hb::link;

HbGoogleRequester::HbGoogleRequester() :
    HbHttpRequester()
{

    connect( this, &HbHttpRequester::requestFinished, this, &HbGoogleRequester::onRequestFinished, Qt::UniqueConnection );
    connect( this, &HbHttpRequester::requestError,    this, &HbGoogleRequester::onRequestError,    Qt::UniqueConnection );
}

quint64 HbGoogleRequester::requestUser( HbO2ServerGoogle * auth )
{

    if( !auth || ( auth->linkStatus() != HbO2::LINKED ) )
    {
        HbError( "Auth null or unlinked." );
        return false;
    }

    QUrl url( "https://www.googleapis.com/oauth2/v1/userinfo" );
    QUrlQuery request( url );

    QHash< QString, QString > params;
    params.insert( OAUTH2_ACCESS_TOKEN, auth->token() );
    params.insert( "alt", "json" );

    request.setQueryItems( HbDictionaryHelper::toPairList< QString, QString >( params ) );
    url.setQuery( request );

    quint64 id = processRequest( url );
    if( id > 0 )
    {
        mRequestTypes.insert( id, HbGoogleObject::OBJECT_USER );
        HbInfo( "Request %lld is sent (%s).", id, HbLatin1( url.toString() ) );
    }

    return id;
}

void HbGoogleRequester::onRequestFinished( quint64 request_id, const QJsonDocument & doc )
{

    HbGoogleObject::ObjectType type = HbGoogleObject::OBJECT_NONE;

    if( mRequestTypes.contains( request_id ) )
    {
        type = mRequestTypes.take( request_id );
    }

    HbInfo( "Request (%lld) of type %s completed.",
            request_id,
            HbLatin1( HbGoogleObject::MetaObjectType::toString( type ) ) );


    if( type == HbGoogleObject::OBJECT_USER )
    {
        HbGoogleUser * user = new HbGoogleUser();
        user->load( doc );
        emit requestCompleted( request_id, user );
    }
    else
    {
        HbError( "Object creation failed, bad type." );
        emit requestCompleted( request_id, nullptr );
    }
}

void HbGoogleRequester::onRequestError( quint64 request_id, const QString & error )
{
    HbGoogleObject::ObjectType type = HbGoogleObject::OBJECT_NONE;

    if( mRequestTypes.contains( request_id ) )
    {
        type = mRequestTypes.take( request_id );
    }

    HbError( "Request (%lld) of type %s failed (%s).",
             request_id,
             HbLatin1( HbGoogleObject::MetaObjectType::toString( type ) ),
             HbLatin1( error ) );

    emit requestCompleted( request_id, nullptr );
}
