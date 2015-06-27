// Qt
// Hb
#include <outputs/HbLogUdpSocketOutput.h>
#include <HbLogMessage.h>

using namespace hb::log;


HbLogUdpSocketOutput::HbLogUdpSocketOutput( quint32 port , HbLogger::Levels level ) :
    QUdpSocket(), HbLogAbstractOutput( OUTPUT_UDP_SOCKET, level )
{
    mPort = port;
}

HbLogUdpSocketOutput::~HbLogUdpSocketOutput()
{

}

quint32 HbLogUdpSocketOutput::port() const
{
    return mPort;
}

void HbLogUdpSocketOutput::processMessage( const HbLogMessage & message )
{
    writeDatagram( message.toByteArray(), QHostAddress( QHostAddress::LocalHost ), mPort );
    flush();
}
