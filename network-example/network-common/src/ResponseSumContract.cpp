// Local
#include <ResponseSumContract.h>
#include <Protocol.h>

using namespace hb::network;
using namespace hb::networkexample;

ResponseSumContract::ResponseSumContract( ) :
    HbNetworkContract( Protocol::CHANNEL_SUM,
                       Protocol::CODE_SRV_RESPONSE_SUM )
{
    setRouting( HbNetworkProtocol::ROUTING_UNICAST );
    mResult = 0;
}

ResponseSumContract::ResponseSumContract( const ResponseSumContract & source ) :
    HbNetworkContract( source )
{
    if( & source != this )
    {
        mResult = source.mResult;
    }
}

ResponseSumContract & ResponseSumContract::operator=(const ResponseSumContract & source)
{
    if( &source != this )
    {
        HbNetworkContract::operator=( source );

        mResult = source.mResult;
    }

    return ( *this );
}

ResponseSumContract * ResponseSumContract::create( ) const
{
    return new ResponseSumContract();
}

const QString ResponseSumContract::toString( ) const
{
    return QString( "%1,result=%2" )
            .arg( HbNetworkContract::toString() )
            .arg( mResult );
}

bool ResponseSumContract::read( QDataStream & stream )
{
    stream >> mResult;

    return true;
}

bool ResponseSumContract::write( QDataStream & stream ) const
{
    stream << mResult;

    return true;
}

qint32 ResponseSumContract::result( ) const
{
    return mResult;
}

void ResponseSumContract::setResult( qint32 result )
{
    mResult = result;
}
