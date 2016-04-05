// Local
#include <RequestSumContract.h>
#include <Protocol.h>

using namespace hb::network;
using namespace hb::networkexample;

RequestSumContract::RequestSumContract() :
    HbNetworkContract( Protocol::CHANNEL_SUM,
                       Protocol::CODE_CLT_REQUEST_SUM )
{
    setRouting( HbNetworkProtocol::ROUTING_UNICAST );
    mIntA = 0;
    mIntB = 0;
    mpReply = new ResponseSumContract();
}

RequestSumContract::RequestSumContract( const RequestSumContract & source ) :
    HbNetworkContract( source )
{
    if( &source != this )
    {
        mIntA = source.mIntA;
        mIntB = source.mIntB;
    }
}

RequestSumContract & RequestSumContract::operator=( const RequestSumContract & source )
{
    if( &source != this )
    {
        HbNetworkContract::operator=( source );

        mIntA = source.mIntA;
        mIntB = source.mIntB;
    }

    return ( *this );
}

RequestSumContract * RequestSumContract::create() const
{
    return new RequestSumContract();
}

ResponseSumContract * RequestSumContract::takeReply() const
{
    return HbNetworkContract::takeReply()->value< ResponseSumContract >();
}

QString RequestSumContract::toString() const
{
    return QString( "%1,intA=%2,intB=%3" )
            .arg( HbNetworkContract::toString() )
            .arg( mIntA )
            .arg( mIntB );
}

bool RequestSumContract::read( QDataStream & stream )
{
    stream >> mIntA;
    stream >> mIntB;

    return true;
}

bool RequestSumContract::write( QDataStream & stream ) const
{
    stream << mIntA;
    stream << mIntB;

    return true;
}

qint32 RequestSumContract::intA() const
{
    return mIntA;
}

void RequestSumContract::setIntA( qint32 a )
{
    mIntA = a;
}

qint32 RequestSumContract::intB() const
{
    return mIntB;
}

void RequestSumContract::setIntB( qint32 b )
{
    mIntB = b;
}
