// Local
#include <ChatMessageBackContract.h>
#include <Protocol.h>

using namespace hb::network;
using namespace hb::networkexample;

ChatMessageBackContract::ChatMessageBackContract( ) :
    HbNetworkContract( Protocol::CHANNEL_CHAT,
                       Protocol::CODE_SRV_CHAT_MESSAGE )
{
    setRouting( HbNetworkProtocol::ROUTING_MULTICAST );
    mMessage = "";
    mAuthor  = "";
}

ChatMessageBackContract::ChatMessageBackContract( const ChatMessageBackContract & source ) :
    HbNetworkContract( source )
{
    if( &source != this )
    {
        mMessage = source.mMessage;
        mAuthor  = source.mAuthor;
    }
}

ChatMessageBackContract & ChatMessageBackContract::operator=(const ChatMessageBackContract & source)
{
    if( &source != this )
    {
        HbNetworkContract::operator=( source );

        mMessage = source.mMessage;
        mAuthor  = source.mAuthor;
    }

    return ( *this );
}

ChatMessageBackContract * ChatMessageBackContract::create( ) const
{
    return new ChatMessageBackContract( );
}

const QString ChatMessageBackContract::toString( ) const
{
    return QString( "%1,message=%2,author=%3" )
            .arg( HbNetworkContract::toString() )
            .arg( mMessage )
            .arg( mAuthor  );
}

bool ChatMessageBackContract::read( QDataStream & stream )
{
    stream >> mMessage;
    stream >> mAuthor;

    return true;
}

bool ChatMessageBackContract::write( QDataStream & stream ) const
{
    stream << mMessage;
    stream << mAuthor;

    return true;
}

void ChatMessageBackContract::setMessage( const QString & message )
{
    mMessage = message;
}

const QString & ChatMessageBackContract::message( ) const
{
    return mMessage;
}

void ChatMessageBackContract::setAuthor( const QString & author )
{
    mAuthor = author;
}

const QString & ChatMessageBackContract::author( ) const
{
    return mAuthor;
}
