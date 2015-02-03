// Qt
#include <QtCore/QMetaType>
// Hb
#include <HbGlobal.h>
#include <HbLogService.h>
// Local
#include <HbPeer.h>
#include <contract/HbNetworkProtocol.h>

using namespace hb::network;

HbPeer::HbPeer( const HbGeneralConfig &config )
{

    qRegisterMetaType< sockuuid >( "sockuuid" );
    qRegisterMetaType< netwuuid >( "netwwuid" );
    qRegisterMetaType< servuuid >( "servuuid" );

    if( config.isValid() )
    {
        HbNetworkProtocol::msAppName = config.appName();
        HbNetworkProtocol::msProtocolVersion = config.protocolVersion();
        mReady = true;
    }
    else
    {
        HbError( "General configuration not valid. HbPeer will never do anything." );
        mReady = false;
    }
}

bool HbPeer::isReady() const
{
    return mReady;
}
