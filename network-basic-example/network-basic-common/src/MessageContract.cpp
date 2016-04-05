// Local
#include <MessageContract.h>
#include <Protocol.h>

using namespace hb::network;
using namespace hb::networkexample;

MessageContract::MessageContract() :
    HbNetworkContract( Protocol::SERVICE_MESSAGE,
                       Protocol::CODE_SRV_MESSAGE )
{
    setRouting( HbNetworkProtocol::ROUTING_MULTICAST );
    mMessage = "";
}

MessageContract::MessageContract( const MessageContract & source ) :
    HbNetworkContract( source )
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
        HbNetworkContract::operator=( source );

        mMessage = source.mMessage;
    }

    return ( *this );
}

MessageContract * MessageContract::create() const
{
    return new MessageContract();
}

QString MessageContract::toString() const
{
    return QString( "%1,message=%2" )
            .arg( HbNetworkContract::toString() )
            .arg( mMessage );
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
