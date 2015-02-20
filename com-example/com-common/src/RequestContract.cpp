// Local
#include <RequestContract.h>
#include <Protocol.h>

using namespace hb::com;
using namespace hb::comexample;

RequestContract::RequestContract() :
    HbComContract( Protocol::SERVICE_QUESTION, Protocol::CODE_CLT_REQUEST )
{
    mRequest = "";
}

RequestContract::RequestContract( const RequestContract & source ) :
    HbComContract( source )
{
    if( &source != this )
    {
        mRequest = source.mRequest;
    }
}

RequestContract & RequestContract::operator=( const RequestContract & source )
{
    if( &source != this )
    {
        HbComContract::operator=( source );

        mRequest = source.mRequest;
    }

    return ( *this );
}

RequestContract * RequestContract::create() const
{
    return new RequestContract();
}

bool RequestContract::read( QDataStream & stream )
{
    stream >> mRequest;

    return true;
}

bool RequestContract::write( QDataStream & stream ) const
{
    stream << mRequest;

    return true;
}

void RequestContract::setRequest( const QString & request )
{
    mRequest = request;
}

const QString & RequestContract::request() const
{
    return mRequest;
}
