// Qt
#include <QtCore/QTimer>
#include <QtNetwork/QUdpSocket>
// Hb
#include <inputs/HbLogUdpSocketInput.h>
#include <HbLogMessage.h>

using namespace hb::log;


HbLogUdpSocketInput::HbLogUdpSocketInput( quint16 port, QObject * parent ) :
    HbLogAbstractInput( parent )
{
    mPort = port;
    mExpected = 0;
}

HbLogUdpSocketInput::~HbLogUdpSocketInput()
{

}

quint16 HbLogUdpSocketInput::port() const
{
    return mPort;
}

void HbLogUdpSocketInput::init()
{
    mUdpSocket.reset( new QUdpSocket() );
    connect( mUdpSocket.data(), &QUdpSocket::readyRead, this, &HbLogUdpSocketInput::onReadyRead );

    onReconnection();
}

void HbLogUdpSocketInput::onReconnection()
{
    if( !mUdpSocket->bind( QHostAddress::LocalHost, mPort ) )
    {
        QTimer::singleShot( 5000, this, &HbLogUdpSocketInput::onReconnection );
        return;
    }
    std::cout << "HbLog: upd input connected on port " << mPort << std::endl;
}

void HbLogUdpSocketInput::onReadyRead()
{
    do
    {
        QByteArray datagram( mUdpSocket->pendingDatagramSize(), 0 );
        mUdpSocket->readDatagram( datagram.data(), datagram.size() );
        QDataStream stream( datagram );
        stream >> mExpected;

        HbLogMessage * message = new HbLogMessage();
        message->fromDataStream( stream );
        emit inputMessageReceived( message );
    }
    while( mUdpSocket->hasPendingDatagrams() );
}
