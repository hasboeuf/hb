// Local
#include <ResponseContract.h>
#include <Protocol.h>

using namespace hb::network;
using namespace hb::networkexample;

ResponseContract::ResponseContract() :
    HbNetworkContract( Protocol::SERVICE_QUESTION,
                       Protocol::CODE_SRV_RESPONSE )
{
    setRouting( HbNetworkProtocol::ROUTING_UNICAST );
    mResponse = "";
}

ResponseContract::ResponseContract( const ResponseContract & source ) :
    HbNetworkContract( source )
{
    if( & source != this )
    {
        mResponse    = source.mResponse;
    }
}

ResponseContract & ResponseContract::operator=( const ResponseContract & source )
{
    if( &source != this )
    {
        HbNetworkContract::operator=( source );

        mResponse    = source.mResponse;
    }

    return ( *this );
}

ResponseContract * ResponseContract::create() const
{
    return new ResponseContract();
}

QString ResponseContract::toString() const
{
    return QString( "%1,response=%2" )
            .arg( HbNetworkContract::toString() )
            .arg( mResponse );
}

bool ResponseContract::read( QDataStream & stream )
{
    stream >> mResponse;

    return true;
}

bool ResponseContract::write( QDataStream & stream ) const
{
    stream << mResponse;

    return true;
}

void ResponseContract::setResponse( const QString & response )
{
    mResponse = response;
}

const QString & ResponseContract::response() const
{
    return mResponse;
}
