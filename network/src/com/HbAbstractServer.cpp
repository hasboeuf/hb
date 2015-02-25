// Qt
#include <QtCore/QDataStream>
#include <QtCore/QSharedPointer>
// Hb
#include <HbLogService.h>
// Local
#include <com/HbAbstractServer.h>
#include <com/HbAbstractSocket.h>
#include <config/com/HbNetworkConfig.h>
#include <contract/HbNetworkHeader.h>
#include <com/HbSocketHandler.h>

using namespace hb::tools;
using namespace hb::network;

HbAbstractServer::HbAbstractServer(QObject * parent) :
    HbAbstractNetwork(parent)
{
    mReady = false;
}


bool HbAbstractServer::join()
{
    if ( !isListening() )
    {
        if( !this->configuration().isValid() )
        {
            HbError( "Invalid server configuration." );
            return false;
        }

        if ( connectToNetwork() )
        {
            mReady = true;
            emit serverConnected( mUid );
        }
    }

    return isListening();
}

bool HbAbstractServer::leave()
{
    if ( isListening() )
    {
        disconnectFromNetwork();
        mReady = false;
        reset();
        emit serverDisconnected( mUid );

        HbInfo( "Server stopped." );
    }
    else
    {
        HbInfo( "Server already stopped." );
    }



    /*QHash< quint32, HbSocketHandler * >::iterator it = mHandlerBySocketId.begin();
    while( it != mHandlerBySocketId.end() )
    {
        quint16 socket_uid = it.key();
        HbSocketHandler * handler = q_assert_ptr( it.value() );

        leave( socket_uid ); // TODO delete thread etc.

        ++it;
    }*/


        // TODO
        //foreach(HbAbstractSocket * socket, _pending)
        //{
        //    disconnect( socket, &HbAbstractSocket::readyPacket, this, nullptr );
        //    disconnect(socket, &HbAbstractSocket::disconnected, this, nullptr);
        //}
        //
        //foreach(HbAbstractSocket * socket, _connected)
        //{
        //    disconnect( socket, &HbAbstractSocket::readyPacket, this, nullptr );
        //    disconnect(socket, &HbAbstractSocket::disconnected, this, nullptr);
        //
        //    emit disconnected(socket->uid());
        //}

        //qDeleteAll(_pending);
        //qDeleteAll(_connected);




    return true;
}

bool HbAbstractServer::leave( networkuid uid )
{
    HbInfo( "Disconnecting socket %d.", uid );
    HbSocketHandler * handler = mHandlerBySocketId.value( uid, nullptr );
    q_assert_ptr( handler );

    bool result = false;
    q_assert( QMetaObject::invokeMethod( handler, "onDisconnectionRequest", Q_ARG( networkuid, uid ) ) );
    return result;

    //QMetaObject::invokeMethod(    handler,
    //                            QStringLiteral("onDisconnectRequest"),
    //                            Q_ARG( quint16, uid ) );

    //HbAbstractSocket * socket = _connected.take(uid);
    //
    //if (!socket)
    //{
    //    raiseError(QAbstractSocket::OperationError,
    //        QStringLiteral("try to close an unregistered client"));
    //}
    //
    //else
    //{
    //    disconnect( socket, &HbAbstractSocket::readyPacket, this, nullptr );
    //    disconnect(socket, &HbAbstractSocket::disconnected, this, nullptr);
    //
    //    if (!disconnectFromNetwork(socket))
    //    {
    //        //connect(socket, &HbAbstractSocket::disconnected, this,
    //        //    [this, socket]() { onClientDisconnect(socket); }, Qt::UniqueConnection);
    //    }
    //
    //    else
    //    {
    //        emit disconnected(uid);
    //        return true;
    //    }
    //}

}

bool HbAbstractServer::isReady() const
{
    return mReady;
}

bool HbAbstractServer::send( ShConstHbNetworkContract contract )
{
    if( contract.isNull() )
    {
        HbWarning( "Try to send a null contract." );
    }
    else
    {
        if ( !isListening() )
        {
            HbError( "Unable to send contract on inactive server" );
        }
        else
        {
            if ( !configuration().exchanges().registered( contract->header().service(), contract->header().code() ) )
            {
                HbError( "Try to send an unregistered contract [service=%d, code=%d]", contract->header().service(), contract->header().code() );

                return false;
            }

            if( contract->routing() == HbNetworkProtocol::UNICAST )
            {
                networkuid receiver = contract->socketReceiver();
                if( receiver != 0 )
                {
                    HbSocketHandler * handler = mHandlerBySocketId.value( receiver, nullptr );
                    if( !handler )
                    {
                        HbWarning( "Unable to send contract, socket %d does not exist.", receiver );
                    }
                    else
                    {
                        q_assert( QMetaObject::invokeMethod( handler, "onSendContract", Q_ARG( networkuid, receiver ), Q_ARG( ShConstHbNetworkContract, contract ) ) );
                    }
                }
                else
                {
                    HbError( "Try to send an incompatible UNICAST contract." );
                }
            }
            else if( contract->routing() == HbNetworkProtocol::MULTICAST )
            {
                // Retrieve socket handler.
                foreach( networkuid receiver, contract->socketReceivers() )
                {
                    HbSocketHandler * handler = mHandlerBySocketId.value( receiver, nullptr );
                    if( !handler )
                    {
                        HbWarning( "Unable to send contract, socket %d does not exist.", receiver );
                    }
                    else
                    {
                        q_assert( QMetaObject::invokeMethod( handler, "onSendContract", Q_ARG( networkuid, receiver ), Q_ARG( ShConstHbNetworkContract, contract ) ) );
                    }
                }
            }
            else // HbNetworkProtocol::BROADCAST
            {
                foreach( HbSocketHandler * handler, mHandlerById.values() )
                {
                    q_assert_ptr( handler );
                    q_assert( QMetaObject::invokeMethod( handler, "onSendContract", Q_ARG( ShConstHbNetworkContract, contract ) ) );
                }
            }
        }
    }

    return false;
}

bool HbAbstractServer::isUidConnected( networkuid uid ) const
{
    return mHandlerBySocketId.contains( uid );
}

const HbServerConfig & HbAbstractServer::configuration() const // SUB
{
    return mConfig;
}

void HbAbstractServer::reset()
{
    HbInfo( "Reset server..." );

    mPending.clear();
    foreach( HbSocketHandler * handler, mHandlerById.values() )
    {
        q_assert_ptr( handler );
        HbInfo( "Deleting handler %d", handler->uid() );
        handler->disconnect();
        handler->deleteLater();
    }
    mPending.clear();
    mHandlerById.clear();
    mHandlerBySocketId.clear();
}


void HbAbstractServer::onSocketConnected( qint32 socket_descriptor, networkuid socket_uid )
{
    if( !mReady )
    {
        HbInfo( "Server not ready, no treatments for onSocketConnected()." );
        return;
    }

    HbSocketHandler * handler = qobject_cast< HbSocketHandler * >( sender() );
    q_assert_ptr( handler );
    q_assert( mPending.contains( socket_descriptor ) );
    q_assert( !mHandlerBySocketId.contains( socket_uid ) );

    HbInfo( "New socket %d connected (descriptor=%d) on handler %d.", socket_uid, socket_descriptor, handler->uid() );

    mPending.removeOne( socket_descriptor );
    mHandlerBySocketId.insert( socket_uid, handler );
}

void HbAbstractServer::onSocketDisconnected( networkuid socket_uid )
{
    if( !mReady )
    {
        HbInfo( "Server not ready, no treatments for onSocketDisconnected()." );
        return;
    }
    HbSocketHandler * handler = qobject_cast< HbSocketHandler * >( sender() );
    q_assert_ptr( handler );
    q_assert( mHandlerBySocketId.value( socket_uid ) == handler );

    mHandlerBySocketId.remove( socket_uid );
}

void HbAbstractServer::onSocketContractReceived( networkuid socket_uid, const HbNetworkContract * contract )
{
    if( !mReady )
    {
        HbInfo( "Server not ready, no treatments for onSocketContractReceived()." );
        delete contract;
        return;
    }
    emit socketContractReceived( mUid, socket_uid, contract );
}

void HbAbstractServer::onHandlerIdled()
{
    if( !mReady )
    {
        HbInfo( "Server not ready, no treatments for onHandlerIdled()." );
        return;
    }
    HbSocketHandler * handler = qobject_cast< HbSocketHandler * >( sender() );
    q_assert_ptr( handler );

    mHandlerById.remove( handler->uid() );

    handler->disconnect();
    handler->deleteLater();
}


