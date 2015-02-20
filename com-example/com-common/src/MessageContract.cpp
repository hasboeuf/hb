// Local
#include <MessageContract.h>
#include <Protocol.h>

using namespace hb::com;
using namespace hb::comexample;

MessageContract::MessageContract() :
    HbComContract( Protocol::SERVICE_MESSAGE, Protocol::CODE_SRV_MESSAGE )
{
    mMessage = "";
}

MessageContract::MessageContract( const MessageContract & source ) :
    HbComContract( source )
{
    if( &source != this )
    {
        mMessage = source.mMessage;
    }
}

MessageContract & MessageContract::operator=( const MessageContract & source )
{
    if( &source != this )
    {
        HbComContract::operator=( source );

        mMessage = source.mMessage;
    }

    return ( *this );
}

MessageContract * MessageContract::create() const
{
    return new MessageContract();
}

bool MessageContract::read( QDataStream & stream )
{
    stream >> mMessage;

    return true;
}

bool MessageContract::write( QDataStream & stream ) const
{
    stream << mMessage;

    return true;
}

void MessageContract::setMessage( const QString & message )
{
    mMessage = message;
}

const QString & MessageContract::message() const
{
    return mMessage;
}
