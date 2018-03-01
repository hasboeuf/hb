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
#include <outputs/HbLogUdpSocketOutput.h>
#include <outputs/HbLogTcpSocketOutput.h>
#include <inputs/HbLogLocalSocketInput.h>
#include <inputs/HbLogUdpSocketInput.h>
#include <inputs/HbLogTcpSocketInput.h>

using namespace hb::log;


HbLoggerPool::HbLoggerPool() :
    QObject()
{
    mAtomic = 0;
    mpClock = nullptr;
    mCapacity = MAX_CAPACITY;
}

HbLoggerPool::~HbLoggerPool()
{
    // Dequeueing events
    q_assert_ptr( mpClock )->deleteLater();
    mpClock = nullptr;

    QCoreApplication::processEvents( QEventLoop::ExcludeUserInputEvents );

    qDeleteAll( mInputs ); // Disconnect inputs.

    while( !mLoggerStream.isEmpty() )
    {
        process();
        QThread::yieldCurrentThread();
    }

    qDeleteAll( mOutputs );
    qDeleteAll( mLoggerStream );
}

loguid HbLoggerPool::addUdpSocketInput( quint16 port, QString * error )
{
    QWriteLocker locker( &mInputsLock );

    HbLogAbstractInput * input = new HbLogUdpSocketInput( port, this );
    input->moveToThread( thread() );
    input->init();

    connect( input, &HbLogUdpSocketInput::inputMessageReceived, this, &HbLoggerPool::onInputMessageReceived );

    mInputs.insert( input->uid(), input );

    return input->uid();
}

loguid HbLoggerPool::addTcpSocketInput( quint16 port, QString * error )
{
    QWriteLocker locker( &mInputsLock );

    HbLogAbstractInput * input = new HbLogTcpSocketInput( port, this );
    input->moveToThread( thread() );
    input->init();

    connect( input, &HbLogUdpSocketInput::inputMessageReceived, this, &HbLoggerPool::onInputMessageReceived );

    mInputs.insert( input->uid(), input );

    return input->uid();
}

loguid HbLoggerPool::addLocalSocketInput( const QString & name, QString * error )
{
    QWriteLocker locker( &mInputsLock );

    HbLogAbstractInput * input = new HbLogLocalSocketInput( name, this );
    input->moveToThread( thread() );
    input->init();

    connect( input, &HbLogUdpSocketInput::inputMessageReceived, this, &HbLoggerPool::onInputMessageReceived );

    mInputs.insert( input->uid(), input );
    return input->uid();
}

bool HbLoggerPool::removeInput( loguid uid, QString * error )
{
    QWriteLocker locker( &mInputsLock );

    HbLogAbstractInput * input = mInputs.take( uid );
    delete input;
    return true;
}

loguid HbLoggerPool::addConsoleOutput( QString * error )
{
    QWriteLocker locker( &mOutputsLock );

    HbLogAbstractOutput * output = new HbLogConsoleOutput();
    output->moveToThread( thread() );
    output->init();
    mOutputs.insert( output->uid(), output );
    return output->uid();
}

loguid HbLoggerPool::addGuiOutput( HbLogGuiNotifier * notifier, QString * error )
{
    QWriteLocker locker( &mOutputsLock );

    HbLogAbstractOutput * output = new HbLogGuiOutput( notifier );
    output->moveToThread( thread() );
    output->init();
    mOutputs.insert( output->uid(), output );
    return output->uid();
}

loguid HbLoggerPool::addFileOutput( const QString & dir, quint32 max_size, QString * error )
{
    QWriteLocker locker( &mOutputsLock );

    HbLogAbstractOutput * output = new HbLogFileOutput( dir, max_size );
    output->moveToThread( thread() );
    output->init();
    mOutputs.insert( output->uid(), output );
    return output->uid();
}

loguid HbLoggerPool::addUdpSocketOutput( const QString & ip, quint16 port, QString * error )
{
    QWriteLocker locker( &mOutputsLock );

    HbLogAbstractOutput * output = new HbLogUdpSocketOutput( ip, port );
    output->moveToThread( thread() );
    output->init();
    mOutputs.insert( output->uid(), output );
    return output->uid();
}

loguid HbLoggerPool::addTcpSocketOutput( const QString & ip, quint16 port, QString * error )
{
    QWriteLocker locker( &mOutputsLock );

    HbLogAbstractOutput * output = new HbLogTcpSocketOutput( ip, port );
    output->moveToThread( thread() );
    output->init();
    mOutputs.insert( output->uid(), output );
    return output->uid();
}

loguid HbLoggerPool::addLocalSocketOutput( const QString & name, QString * error )
{
    QWriteLocker locker( &mOutputsLock );

    HbLogAbstractOutput * output = new HbLogLocalSocketOutput( name );
    output->moveToThread( thread() );
    output->init();
    mOutputs.insert( output->uid(), output );
    return output->uid();
}

bool HbLoggerPool::removeOutput( loguid uid, QString * error )
{
    QWriteLocker locker( &mOutputsLock );

    HbLogAbstractOutput * output = mOutputs.take( uid );
    delete output;
    return true;
}


HbLogAbstractInput * HbLoggerPool::input( loguid uid )
{
    QReadLocker locker( &mInputsLock );
    return mInputs.value( uid, nullptr );
}

HbLogAbstractOutput * HbLoggerPool::output( loguid uid )
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
    q_assert( mpClock == nullptr );
    mpClock = q_check_ptr( new QTimer() );

    q_assert( connect( mpClock, &QTimer::timeout,
        this, &HbLoggerPool::process, Qt::UniqueConnection ) );

    mpClock->setInterval( 1 );
    mpClock->start();
}

void HbLoggerPool::onInputMessageReceived( HbLogMessage * message )
{
    mInputsStream.push_back( message );
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

                    for( HbLogAbstractOutput * output: mOutputs.values() )
                    {
                        output->processMessage( *message );
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
