// Qt
#include <QtCore/QCoreApplication>
#include <QtCore/QThread>
#include <QtCore/QTimer>
// Hb
#include <HbGlobal.h>
#include <HbLoggerPool.h>
#include <HbLogMessage.h>
#include <outputs/HbLogConsoleOutput.h>
#include <outputs/HbLogFileOutput.h>
#include <outputs/HbLogGuiOutput.h>
#include <outputs/HbLogLocalSocketOutput.h>
#include <outputs/HbLogTcpSocketOutput.h>
#include <inputs/HbLogLocalSocketInput.h>
#include <inputs/HbLogTcpSocketInput.h>

using namespace hb::log;


HbLoggerPool::HbLoggerPool( QThread * thread ) :
    QObject()
{
    mAtomic = 0;
    mpClock = nullptr;
	mCapacity = MAX_CAPACITY;

    q_assert( connect( q_assert_ptr( thread ), &QThread::started,
        this, &HbLoggerPool::running, Qt::UniqueConnection ) );
}

HbLoggerPool::~HbLoggerPool()
{
    // Dequeueing events
    q_assert_ptr( mpClock )->stop();
	QCoreApplication::processEvents( QEventLoop::ExcludeUserInputEvents ); 

    qDeleteAll( mInputs );
    qDeleteAll( mOutputs );
    qDeleteAll( mLoggerStream );
}


loguid HbLoggerPool::addTcpSocketInput( quint16 port, QString * error )
{
    QWriteLocker locker( &mInputsLock );
    HbLoggerStream::State state = HbLoggerStream::INOUT_ADD_SUCCESS;

    if ( port < TCP_PORT_MIN || port > TCP_PORT_MAX )
    {
        state = HbLoggerStream::INOUT_WRONG_PARAMETERS;
    }

    if( state == HbLoggerStream::INOUT_ADD_SUCCESS )
    {
        foreach( HbLogAbstractInput* input, mInputs )
        {
            if( q_assert_ptr( input )->type() == HbLogAbstractInput::INPUT_TCP_SOCKET )
            {
                HbLogTcpSocketInput * tcpServer = q_dynamic_cast( HbLogTcpSocketInput *, input );

                if( tcpServer->port() == port )
                {
                    state = HbLoggerStream::INOUT_ALREADY_EXISTS;
                    break;
                }
            }
        }
    }

    if( state == HbLoggerStream::INOUT_ADD_SUCCESS )
    {
        HbLogTcpSocketInput * input = q_check_ptr( new HbLogTcpSocketInput( port ) );
        input->moveToThread( thread() );

        q_assert( connect( input, &HbLogTcpSocketInput::inputMessageReceived, this,
            [this]( HbLogMessage * message )
            {
                mInputsStream.push_back( q_assert_ptr( message ) );
            }, Qt::UniqueConnection ) );

        mInputs.insert( input->uid(), input );

        return input->uid();
    }

    if( error )
    {
        ( *error ) = HbLoggerStream::MetaState::toString( state );
    }
    return 0;
}

loguid HbLoggerPool::addLocalSocketInput( const QString & name, QString * error )
{
    QWriteLocker locker( &mInputsLock );
    HbLoggerStream::State state = HbLoggerStream::INOUT_ADD_SUCCESS;

    if( state == HbLoggerStream::INOUT_ADD_SUCCESS )
    {
        foreach( HbLogAbstractInput * input, mInputs )
            if( q_assert_ptr( input )->type() == HbLogAbstractInput::INPUT_LOCAL_SOCKET )
            {
                state = HbLoggerStream::INOUT_ALREADY_EXISTS;
                break;
            }
    }

    if( state == HbLoggerStream::INOUT_ADD_SUCCESS )
    {
        HbLogLocalSocketInput * input = q_check_ptr( new HbLogLocalSocketInput( name ) );
        input->moveToThread( thread() );

        q_assert( connect( input, &HbLogLocalSocketInput::inputMessageReceived, this,
            [this]( HbLogMessage * message )
            {
                mInputsStream.push_back( q_assert_ptr( message ) );
            }, Qt::UniqueConnection ) );

        mInputs.insert( input->uid(), input );
        return input->uid();
    }

    if( error )
    {
        ( *error ) = HbLoggerStream::MetaState::toString( state );
    }
    return 0;
}

bool HbLoggerPool::removeInput( loguid uid, QString * error )
{
    QWriteLocker locker( &mInputsLock );
    HbLoggerStream::State state = HbLoggerStream::INOUT_DEL_FAIL;

    HbLogAbstractInput * input = mInputs.take( uid );

    if( input )
    {
        delete input;
        state = HbLoggerStream::INOUT_DEL_SUCCESS;
    }

    if( error )
    {
        ( *error ) = HbLoggerStream::MetaState::toString( state );
    }
    return ( state == HbLoggerStream::INOUT_DEL_SUCCESS );
}


loguid HbLoggerPool::addConsoleOutput( QString * error )
{
    QWriteLocker locker( &mOutputsLock );
	HbLoggerStream::State state = HbLoggerStream::INOUT_ADD_SUCCESS;

    if( state == HbLoggerStream::INOUT_ADD_SUCCESS )
    {
		foreach(HbLogAbstractOutput * output, mOutputs)
		{
			if (q_assert_ptr(output)->type() == HbLogAbstractOutput::OUTPUT_CONSOLE)
			{
				state = HbLoggerStream::INOUT_CONSOLE_ALREADY_EXISTS;
				break;
			}
		}
    }

	if( state == HbLoggerStream::INOUT_ADD_SUCCESS )
    {
        HbLogConsoleOutput * output = q_assert_ptr( new HbLogConsoleOutput( HbLogger::LEVEL_ALL ) );
        mOutputs.insert( output->uid(), output );
        return output->uid();
    }

    if( error )
    {
        ( *error ) = HbLoggerStream::MetaState::toString( state );
    }
    return 0;
}

loguid HbLoggerPool::addGuiOutput( HbLogGuiNotifier * notifier, QString * error )
{
    QWriteLocker locker( &mOutputsLock );
    HbLoggerStream::State state = HbLoggerStream::INOUT_ADD_SUCCESS;

    if( state == HbLoggerStream::INOUT_ADD_SUCCESS )
        if( !notifier ) state = HbLoggerStream::INOUT_WRONG_PARAMETERS;

    if( state == HbLoggerStream::INOUT_ADD_SUCCESS )
    {
        HbLogGuiOutput * output = q_check_ptr( new HbLogGuiOutput( notifier, HbLogger::LEVEL_ALL ) );
        mOutputs.insert( output->uid(), output );
        return output->uid();
    }

    if( error )
    {
        ( *error ) = HbLoggerStream::MetaState::toString( state );
    }
    return 0;
}

loguid HbLoggerPool::addFileOutput( const QString & path, quint32 max_size, QString * error )
{
    QWriteLocker locker( &mOutputsLock );
	HbLoggerStream::State state = HbLoggerStream::INOUT_ADD_SUCCESS;
	
    if( state == HbLoggerStream::INOUT_ADD_SUCCESS )
        if( path.isEmpty() ) state = HbLoggerStream::INOUT_WRONG_PARAMETERS;

	// No existing check as the file_name will never be the same at the end in HbLogFileOutput.

	if( state == HbLoggerStream::INOUT_ADD_SUCCESS )
    {
        HbLogFileOutput * output = q_check_ptr( new HbLogFileOutput( path, max_size, HbLogger::LEVEL_ALL ) );
        mOutputs.insert( output->uid(), output );
        return output->uid();
    }

    if( error )
    {
        ( *error ) = HbLoggerStream::MetaState::toString( state );
    }
    return 0;
}

loguid HbLoggerPool::addTcpSocketOutput( const QString & ip, quint16 port, QString * error )
{
    QWriteLocker locker( &mOutputsLock );
	HbLoggerStream::State state = HbLoggerStream::INOUT_ADD_SUCCESS;

    if( state == HbLoggerStream::INOUT_ADD_SUCCESS )
    {
        if( ip.isEmpty() ) state = HbLoggerStream::INOUT_WRONG_PARAMETERS;
		else if (port < TCP_PORT_MIN || port > TCP_PORT_MAX) state = HbLoggerStream::INOUT_WRONG_PARAMETERS;
    }

    if( state == HbLoggerStream::INOUT_ADD_SUCCESS )
    {
        foreach( HbLogAbstractOutput* output, mOutputs )
            if( q_assert_ptr( output )->type() == HbLogAbstractOutput::OUTPUT_TCP_SOCKET )
            {
                HbLogTcpSocketOutput * tcpSocket = q_dynamic_cast( HbLogTcpSocketOutput *, output );

                if( ( tcpSocket->ip() == ip ) && ( tcpSocket->port() == port ) )
                {
                    state = HbLoggerStream::INOUT_ALREADY_EXISTS;
                    break;
                }
            }
    }

	if( state == HbLoggerStream::INOUT_ADD_SUCCESS )
    {
        HbLogTcpSocketOutput * output = q_check_ptr( new HbLogTcpSocketOutput( ip, port, HbLogger::LEVEL_ALL ) );
        output->moveToThread( thread() );
        mOutputs.insert( output->uid(), output );
        return output->uid();
    }

    if( error )
    {
        ( *error ) = HbLoggerStream::MetaState::toString( state );
    }
    return 0;
}

loguid HbLoggerPool::addLocalSocketOutput( const QString & name, QString * error )
{
    QWriteLocker locker( &mOutputsLock );
	HbLoggerStream::State state = HbLoggerStream::INOUT_ADD_SUCCESS;

    if( state == HbLoggerStream::INOUT_ADD_SUCCESS )
    {
        foreach( HbLogAbstractOutput* output, mOutputs )
            if( q_assert_ptr( output )->type() == HbLogAbstractOutput::OUTPUT_LOCAL_SOCKET )
            {
                state = HbLoggerStream::INOUT_ALREADY_EXISTS;
                break;
            }
    }

	if( state == HbLoggerStream::INOUT_ADD_SUCCESS )
    {
        HbLogLocalSocketOutput * output = q_check_ptr( new HbLogLocalSocketOutput( name, HbLogger::LEVEL_ALL ) );
        output->moveToThread( thread() );
        mOutputs.insert( output->uid(), output );
        return output->uid();
    }

    if( error )
    {
        ( *error ) = HbLoggerStream::MetaState::toString( state );
    }
    return 0;
}

bool HbLoggerPool::removeOutput( loguid uid, QString * error )
{
    QWriteLocker locker( &mOutputsLock );
	HbLoggerStream::State state = HbLoggerStream::INOUT_DEL_FAIL;

    HbLogAbstractOutput * output = mOutputs.take( uid );

    if( output )
    {
        delete output;
        state = HbLoggerStream::INOUT_DEL_SUCCESS;
    }

    if( error )
    {
        ( *error ) = HbLoggerStream::MetaState::toString( state );
    }
    return ( state == HbLoggerStream::INOUT_DEL_SUCCESS );
}


IHbLoggerInput * HbLoggerPool::input( loguid uid )
{
    QReadLocker locker( &mInputsLock );
    return mInputs.value( uid, nullptr );
}

IHbLoggerOutput * HbLoggerPool::output( loguid uid )
{
    QReadLocker locker( &mOutputsLock );
    return mOutputs.value( uid, nullptr );
}


bool HbLoggerPool::enqueueMessage( QList< HbLogMessage * > & buffer )
{
    if( mAtomic.testAndSetOrdered( 0, 1 ) )
    {

        while( !buffer.isEmpty() )
        {
            if ( mLoggerStream.size() == mCapacity )
			{
				delete mLoggerStream.takeFirst();
			}

            mLoggerStream.push_back( buffer.takeFirst() );
        }

        mAtomic.fetchAndStoreOrdered( 0 );
        return true;
    }

    return false;
}


void HbLoggerPool::running()
{

    Q_ASSERT( mpClock == nullptr );
    mpClock = q_check_ptr( new QTimer( this ) );

	q_assert(connect(mpClock, &QTimer::timeout,
        this, &HbLoggerPool::process, Qt::UniqueConnection ) );

    mpClock->setInterval( 1 );
    mpClock->start();
}

void HbLoggerPool::process()
{
    if( mAtomic.testAndSetOrdered( 0, 1 ) )
    {
        // Dequeue messages coming from inputs.
        while ( !mInputsStream.isEmpty() )
        {
            if ( mLoggerStream.size() == mCapacity )
            {
                delete mLoggerStream.takeFirst();
            }

            mLoggerStream.push_back( mInputsStream.takeFirst() );
        }

        { // Dequeue general message list.
            QReadLocker locker( &mOutputsLock );
            if ( mOutputs.size() > 0 )
            {
                while( !mLoggerStream.isEmpty() )
                {
                    HbLogMessage * message = q_assert_ptr( mLoggerStream.takeFirst() );

                    foreach( HbLogAbstractOutput * output, mOutputs.values() )
                    {
                        if ( output->isValid() )
                        {
                            if ( output->level() & message->level() )
                            {
                                output->processMessage( *message );
                            }
                        }
                    }

                    if (message)
                    {
                        delete message;
                    }
                }
            }
        }

        mAtomic.fetchAndStoreOrdered( 0 );
    }
}
