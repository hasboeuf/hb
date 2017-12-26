// Qt
#include <QtNetwork/QTcpSocket>
// Hb
#include <HbLogService.h>
// Local
#include <com/tcp/HbTcpSocket.h>

using namespace hb::network;


HbTcpSocket::HbTcpSocket( QTcpSocket * device ) :
    HbAbstractSocket( device )
{
    q_assert_ptr( device );
    mpDevice = device;

    connect( mpDevice, &QTcpSocket::stateChanged, this, &HbTcpSocket::onStateChanged, Qt::UniqueConnection );
    connect( mpDevice, ( void (QTcpSocket::*)( QAbstractSocket::SocketError ) ) &QTcpSocket::error,
    [this]()
    {
        emit socketError();
    } );
}

HbTcpSocket::~HbTcpSocket()
{
    // HbAbstractSocket handles the destruction.
}


HbNetworkProtocol::NetworkType HbTcpSocket::type() const
{
    return HbNetworkProtocol::NETWORK_TCP;
}


bool HbTcpSocket::connectToHost(const HbTcpConfig & config)
{
    if ( state() == QAbstractSocket::UnconnectedState)
    {
        mConfig = config;
        mpDevice->connectToHost( mConfig.address(), mConfig.port(), QIODevice::ReadWrite );

        return true;
    }

    return false;
}

bool HbTcpSocket::leave()
{
    if ( state() != QAbstractSocket::UnconnectedState)
    {
        mpDevice->disconnectFromHost();
        return true;
    }

    return false;
}


bool HbTcpSocket::isListening() const
{
    return ( state() == QAbstractSocket::ConnectedState );
}


void HbTcpSocket::setSocketOption( QAbstractSocket::SocketOption option, bool enable )
{
    switch ( option )
    {
    case QAbstractSocket::LowDelayOption:
    case QAbstractSocket::KeepAliveOption:
    case QAbstractSocket::MulticastLoopbackOption:

        mpDevice->setSocketOption( option, enable );
        break;

    default:

        Q_UNREACHABLE();
        break;
    }
}

bool HbTcpSocket::socketOption( QAbstractSocket::SocketOption option ) const
{
    switch ( option )
    {
    case QAbstractSocket::LowDelayOption:
    case QAbstractSocket::KeepAliveOption:
    case QAbstractSocket::MulticastLoopbackOption:
        return mpDevice->socketOption( option ).toBool();

    default:
        return false;
    }
}


QAbstractSocket::SocketError HbTcpSocket::error() const
{
    return mpDevice->error();
}

QAbstractSocket::SocketState HbTcpSocket::state() const
{
    return mpDevice->state();
}


void HbTcpSocket::onReadyRead()
{
    QDataStream stream( mpDevice );

    if ( readStream( stream ) < 0 )
    {
        HbError( "Read stream failed." );
    }
}

void HbTcpSocket::onStateChanged( QAbstractSocket::SocketState state )
{
    q_assert( mpDevice == sender() );

    if( state == QAbstractSocket::UnconnectedState )
    {
        HbInfo( "Socket enters UnconnectedState." );
        emit socketDisconnected();
    }
    else if( state == QAbstractSocket::HostLookupState )
    {
        HbInfo( "Socket enters HostLookupState." );
    }
    else if( state == QAbstractSocket::ConnectingState )
    {
        HbInfo( "Socket enters ConnectingState." );
    }
    else if( state == QAbstractSocket::ConnectedState )
    {
        HbInfo( "Socket enters ConnectedState." );
        emit socketConnected();
    }
    else if( state == QAbstractSocket::BoundState )
    {
        HbInfo( "Socket enters BoundState." );
    }
    else if( state == QAbstractSocket::ClosingState )
    {
        HbInfo( "Socket enters ClosingState." );
    }
    else if( state == QAbstractSocket::ListeningState )
    {
        HbInfo( "Socket enters ListeningState." );
    }

    emit socketStateChanged();
}
