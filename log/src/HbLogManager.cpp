// Qt
#include <QtCore/QCoreApplication>
#include <QtCore/QTime>
#include <QtCore/QThread>
// Hb
#include <HbLogManager.h>
#include <HbLoggerInputs.h>
#include <HbLoggerOutputs.h>
#include <HbLoggerPool.h>
#include <HbLogMessage.h>
#include <native/HbLogHandler.h>
#include <core/HbSteadyDateTime.h>

using namespace hb::log;
using namespace hb::tools;


QMutex HbLogManager::msMutex;
quint8 HbLogManager::msInstances = 0;

QThread *      HbLogManager::msThreadPool = nullptr;
HbLoggerPool * HbLogManager::msLoggerPool = nullptr;


HbLogManager::HbLogManager() :
    QObject(), HbLogger()
{
    msMutex.lock();

    if( ++msInstances == 1 )
    {
		qRegisterMetaType< hb::log::HbLoggerStream::State >( "HbLoggerStream::State" );
		qRegisterMetaType< hb::log::HbLogMessage >( "HbLogMessage" );

        msThreadPool = q_check_ptr( new QThread() );
        msLoggerPool = q_check_ptr( new HbLoggerPool( msThreadPool ) );

        q_assert( connect( msThreadPool, &QThread::finished,
            msThreadPool, &QObject::deleteLater, Qt::UniqueConnection ) );

        msLoggerPool->moveToThread( msThreadPool );
        msThreadPool->start();
	}

    msMutex.unlock();


    mpInputs = q_check_ptr( new HbLoggerInputs( this ) );
    mpOutputs = q_check_ptr( new HbLoggerOutputs( this ) );

    /*q_assert( connect( msLoggerPool, ( void ( HbLoggerPool::* )( quint32, HbLoggerStream::State ) ) &HbLoggerPool::streamState,
        mpInputs, ( void ( HbLoggerStream::* )( quint32, HbLoggerStream::State ) ) &HbLoggerStream::streamState,
        static_cast< Qt::ConnectionType >( Qt::DirectConnection | Qt::UniqueConnection ) ) );

    q_assert( connect( msLoggerPool, ( void ( HbLoggerPool::* )( quint32, HbLoggerStream::State ) ) &HbLoggerPool::streamState,
        mpOutputs, ( void ( HbLoggerStream::* )( quint32, HbLoggerStream::State ) ) &HbLoggerStream::streamState,
        static_cast< Qt::ConnectionType >( Qt::DirectConnection | Qt::UniqueConnection ) ) );*/

	q_assert(connect(msLoggerPool, &HbLoggerPool::streamStateChanged,
		mpInputs, &HbLoggerStream::onStreamStateChanged,
		static_cast< Qt::ConnectionType >(Qt::DirectConnection | Qt::UniqueConnection)));

	q_assert(connect(msLoggerPool, &HbLoggerPool::streamStateChanged,
		mpOutputs, &HbLoggerStream::onStreamStateChanged,
		static_cast< Qt::ConnectionType >(Qt::DirectConnection | Qt::UniqueConnection)));
}

HbLogManager::~HbLogManager()
{
	// Send via signals/slots log message that remains in the buffer.
    dequeuePendingMessages();

	msMutex.lock();  // Wait forever.

	if( --msInstances == 0 )
	{
		msThreadPool->exit();
		msThreadPool->wait();

        q_delete_ptr( &msLoggerPool );
	}

    msMutex.unlock();
}


HbLoggerInputs * HbLogManager::inputs() const
{
    return q_assert_ptr( mpInputs );
}

HbLoggerOutputs * HbLogManager::outputs() const
{
    return q_assert_ptr( mpOutputs );
}

HbLoggerPool * HbLogManager::pool() const
{
    return q_assert_ptr( msLoggerPool );
}

void HbLogManager::enqueueMessage( Level level, Formats format, const HbLogContext & context, const QString & text )
{
    qint64 timestamp = HbSteadyDateTime::now().toNsSinceEpoch();

    HbLogMessage * message = q_check_ptr( new HbLogMessage( level, format, context, timestamp, text ) );

    mMessages.push_back( message );
	msLoggerPool->enqueueMessage( mMessages );
}

void HbLogManager::dequeuePendingMessages()
{
    if( !mMessages.isEmpty() )
    {
        while( !msLoggerPool->enqueueMessage( mMessages ) )
            QThread::yieldCurrentThread();
    }
}
