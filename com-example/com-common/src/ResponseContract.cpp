// Local
#include <ResponseContract.h>
#include <Protocol.h>

using namespace hb::com;
using namespace hb::comexample;

ResponseContract::ResponseContract() :
    HbComContract( Protocol::SERVICE_QUESTION, Protocol::CODE_SRV_RESPONSE )
{
    mResponse = "";
}

ResponseContract::ResponseContract( const ResponseContract & source ) :
    HbComContract( source )
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
        HbComContract::operator=( source );

        mResponse    = source.mResponse;
    }

    return ( *this );
}

ResponseContract * ResponseContract::create() const
{
    return new ResponseContract();
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
