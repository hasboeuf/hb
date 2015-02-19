// Qt
#include <QtCore/QTimer>
#include <QtCore/QMutexLocker>
#include <QtNetwork/QTcpSocket>
// Hb
#include <HbGlobal.h>
#include <HbLogService.h>
// Local
#include <com/HbSocketHandler.h>
#include <com/HbAbstractServer.h>
#include <com/HbAbstractSocket.h>
#include <config/com/HbNetworkConfig.h>
#include <HbNetworkError.h>
#include <contract/HbNetworkHeader.h>

using namespace hb::tools;
using namespace hb::log;
using namespace hb::network;

HbSocketHandler::HbSocketHandler( HbAbstractServer * server ) :
    QObject( nullptr )
{
    HbLogBegin();

    mState = NOT_THREADED;
    mpServer = q_assert_ptr( server );

    HbLogEnd();
}

HbSocketHandler::~HbSocketHandler()
{
    reset();
}

HbAbstractServer * HbSocketHandler::server() const
{
    return mpServer;
}

void HbSocketHandler::init()
{
    HbLogBegin();

    mState = THREADED;

    HbLogEnd();
}

void HbSocketHandler::reset()
{
    HbInfo( "Reset socket handler #%d", mUid );
    QMutexLocker locker( &mSocketMutex );

    foreach( HbAbstractSocket * socket, mSocketById.values() )
    {
        HbInfo( "Delete socket #%d.", socket->uid() );
        delete socket;
    }

    mSocketById.clear();
    mIdBySocket.clear();
}

bool HbSocketHandler::canHandleNewConnection()
{
    HbLogBegin();

    QMutexLocker locker( &mSocketMutex );

    bool is_threaded = mpServer->configuration().isThreaded();
    if( !is_threaded ||
        (is_threaded &&
         mState == THREADED &&
         mSocketById.size() < mpServer->configuration().maxUsersPerThread() ) )
    {
        return true;
    }

    HbError("SocketHandler#%d: Cannot handle new socket. [state=%d, size=%d, max=%d].",
            mUid,
            mState,
            mSocketById.size(),
            mpServer->configuration().maxUsersPerThread() );

    HbLogEnd();
    return false;
}

bool HbSocketHandler::storeNewSocket(HbAbstractSocket * socket, qint32 previous_uid )
{
    QMutexLocker locker( &mSocketMutex );

    // Q_ASSERT( socket->type( ) != HbAbstractSocket::UdpSocket );

    q_assert_ptr( socket );

    mSocketById.insert( socket->uid( ), socket );
    mIdBySocket.insert( socket, socket->uid( ) );

    connect( socket, &HbAbstractSocket::socketReadyPacket,  this, &HbSocketHandler::onSocketReadyPacket );
    connect( socket, &HbAbstractSocket::socketDisconnected, this, &HbSocketHandler::onSocketDisconnected );
    connect( socket, &HbAbstractSocket::socketError,
             this, [this, socket]()
             {
                 HbError( "Error %d (%s) on socket %d.", socket->error(), HbLatin1( socket->errorString() ), socket->uid());

             }, Qt::UniqueConnection );

    emit socketConnected( previous_uid, socket->uid() ); // To Server.

    return true;
}



void HbSocketHandler::onDisconnectionRequest(quint16 uid )
{
    QMutexLocker locker( &mSocketMutex );

    HbAbstractSocket * socket = mSocketById.value( uid, nullptr );
    if( socket )
    {
        // socket->leave();

        // onSocketDisconnected handles the rest.
    }
    else
    {
        HbWarning( "Socket #%d does not exist for hander #%d.", uid, mUid );
    }
}

void HbSocketHandler::onServerLeft()
{
    HbInfo( "Server left -> deleting this handler #%d", mUid );
    reset();
}

void HbSocketHandler::onSocketReadyPacket()
{
    HbAbstractSocket * socket = q_assert_ptr( dynamic_cast<HbAbstractSocket *>( sender( )) );

    bool available = ( socket->isListening() && socket->packetAvailable() );

    while( available )
    {
        QByteArray packet = socket->readPacket( );

        if( !mpServer->configuration().openMode( ).testFlag( QIODevice::ReadOnly ) )
        {
            HbError( "Unable to receive contract on write only socket %d.", socket->uid() );
        }
        else
        {
            QDataStream stream( &packet, QIODevice::ReadOnly );

            HbNetworkHeader header;
            stream >> header;
            q_assert( stream.status() == QDataStream::Ok );

            HbNetworkContract * contract = mpServer->configuration().exchanges().contract( header );

            if( !contract )
            {
                HbError( "Try to read unregistered contract [service=%d, code=%d].", header.service(), header.code() );
            }
            else
            {
                if( !contract->read( stream ) )
                {
                    q_assert( stream.status( ) == QDataStream::Ok );

                    HbError( "Error occurred while reading contract [service=%d, code=%d].", header.service(), header.code() );
                }
                else
                {
                    contract->setNetworkType( server()->type() );
                    emit socketContractReceived( socket->uid(), contract );
                }
            }
        }

        available = ( socket->isListening() && socket->packetAvailable() );
    }
}

void HbSocketHandler::onSocketDisconnected()
{
    HbLogBegin();

    QMutexLocker locker( &mSocketMutex );

    HbAbstractSocket * socket = q_assert_ptr( dynamic_cast<HbAbstractSocket *>(sender() ) );

    q_assert( mIdBySocket.contains( socket ) );
    q_assert( mSocketById.contains( socket->uid( ) ) );

    HbInfo("SocketPool%d: Socket#%d disconnected.", mUid, socket->uid() );

    sockuid uid = socket->uid();

    mIdBySocket.remove( socket );
    mSocketById.remove( uid );

    socket->disconnect();
    socket->deleteLater();

    emit socketDisconnected( uid );


    if( mSocketById.isEmpty() )
    {
        emit handlerIdled();
    }

    HbLogEnd();

}
