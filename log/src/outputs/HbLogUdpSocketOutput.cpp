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
    /*qint64 written = writeDatagram( message.toByteArray(), QHostAddress( QHostAddress::LocalHost ), mPort );
    flush();*/
}
