// Qt
#include <QtNetwork/QUdpSocket>
// Hb
#include <outputs/HbLogUdpSocketOutput.h>
#include <HbLogMessage.h>

using namespace hb::log;


HbLogUdpSocketOutput::HbLogUdpSocketOutput( const QString & ip, quint16 port, QObject * parent ) :
    HbLogAbstractOutput( parent )
{
    mIp = ip;
    mPort = port;
}

HbLogUdpSocketOutput::~HbLogUdpSocketOutput()
{

}

quint16 HbLogUdpSocketOutput::port() const
{
    return mPort;
}

void HbLogUdpSocketOutput::init()
{
    mUdpSocket.reset( new QUdpSocket() );
}

void HbLogUdpSocketOutput::processMessage( const HbLogMessagePtr & message )
{
    mUdpSocket->writeDatagram( message->toByteArray(), QHostAddress( mIp ), mPort );
    mUdpSocket->flush();
}
