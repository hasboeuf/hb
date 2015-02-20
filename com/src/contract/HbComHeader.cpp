#include <contract/HbComHeader.h>

#include <QDataStream>

using namespace hb::com;


HbComHeader::HbComHeader()
{
    mAppName = HbComProtocol::msAppName;
    mProtocolVersion = HbComProtocol::msProtocolVersion;
    mService = HbComProtocol::SERVICE_UNDEFINED;
    mCode    = HbComProtocol::CODE_UNDEFINED;
}

HbComHeader::HbComHeader(servuid service, codeuid code ) :
    HbComHeader()
{
    mService = service;
    mCode = code;
}

HbComHeader::HbComHeader( const HbComHeader & header )
{
    if( &header != this )
    {
        mAppName         = header.mAppName;
        mProtocolVersion = header.mProtocolVersion;
        mService         = header.mService;
        mCode            = header.mCode;
    }
}

HbComHeader & HbComHeader::operator=( const HbComHeader & header )
{
    if( &header != this )
    {
        mAppName         = header.mAppName;
        mProtocolVersion = header.mProtocolVersion;
        mService         = header.mService;
        mCode            = header.mCode;
    }
    return *this;
}

const QString & HbComHeader::appName() const
{
    return mAppName;
}

quint16 HbComHeader::protocolVersion() const
{
    return mProtocolVersion;
}

servuid HbComHeader::service() const
{
    return mService;
}

codeuid HbComHeader::code() const
{
    return mCode;
}

namespace hb
{
    namespace com
    {

        QDataStream & operator <<(QDataStream & stream, const HbComHeader & header)
        {
            stream << header.mAppName;
            stream << header.mProtocolVersion;
            stream << header.mService;
            stream << header.mCode;

            return stream;
        }

        QDataStream & operator >>(QDataStream & stream, HbComHeader & header)
        {
            stream >> header.mAppName;
            stream >> header.mProtocolVersion;
            stream >> header.mService;
            stream >> header.mCode;

            return stream;
        }
    }
}

/*void HbComContract::setRouting( HbComProtocol::RoutingScheme routing)
{
    if (mRouting != routing)
    {
        mRouting = routing;

        if ( mRouting == HbComProtocol::RoutingScheme::BROADCAST )
        {
            if ( mSocketReceivers.size() > 0)
            {
                HbWarning( "Predefined receivers will be cleared." );
            }

            resetReceivers();
        }

        if ( mRouting == HbComProtocol::RoutingScheme::UNICAST )
        {
            if ( mSocketReceivers.size() > 1 )
            {
                HbWarning( "Only the first receiver is kept." );

                int receiver = *mSocketReceivers.begin();

                resetReceivers();
                mSocketReceivers.insert( receiver );
            }
        }
    }
}

HbComProtocol::RoutingScheme HbComContract::routing() const
{
    if( mRouting == HbComProtocol::RoutingScheme::MULTICAST && mSocketReceivers.isEmpty() )
    {
        return HbComProtocol::RoutingScheme::BROADCAST;
    }

    return mRouting;
}*/
