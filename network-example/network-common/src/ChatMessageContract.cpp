// Local
#include <ChatMessageContract.h>
#include <Protocol.h>

using namespace hb::network;
using namespace hb::networkexample;

ChatMessageContract::ChatMessageContract() :
    HbNetworkContract( Protocol::CHANNEL_CHAT,
                       Protocol::CODE_CLT_CHAT_MESSAGE )
{
    setRouting( HbNetworkProtocol::ROUTING_UNICAST );
    mMessage = "";
}

ChatMessageContract::ChatMessageContract( const ChatMessageContract & source ) :
    HbNetworkContract( source )
{
    if( &source != this )
    {
        mMessage = source.mMessage;
    }
}

ChatMessageContract & ChatMessageContract::operator=(const ChatMessageContract & source)
{
    if( &source != this )
    {
        HbNetworkContract::operator=( source );

        mMessage = source.mMessage;
    }

    return ( *this );
}

ChatMessageContract * ChatMessageContract::create() const
{
    return new ChatMessageContract();
}

QString ChatMessageContract::toString( ) const
{
    return QString( "%1,message=%2" )
            .arg( HbNetworkContract::toString() )
            .arg( mMessage );
}

bool ChatMessageContract::read( QDataStream & stream )
{
    stream >> mMessage;

    return true;
}

bool ChatMessageContract::write( QDataStream & stream ) const
{
    stream << mMessage;

    return true;
}

void ChatMessageContract::setMessage( const QString & message )
{
    mMessage = message;
}

const QString & ChatMessageContract::message( ) const
{
    return mMessage;
}
