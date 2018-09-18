// System
#include <iostream>
// Qt
#include <QtCore/QCoreApplication>
#include <QtCore/QThread>
// Hb
#include <HbLogService.h>
#include <HbLogManager.h>
#include <HbLogMessage.h>
#include <HbLoggerPool.h>
#include <HbLogArgumentParser.h>

using namespace hb::log;


void qtHbLogHandler( QtMsgType type, const QMessageLogContext & context, const QString & message )
{
    HbLogContext( context ).print( type, message );
    if ( type == QtFatalMsg ) {
        abort();
    }
}

namespace hb {
    namespace log {

        class HbLogServiceController
        {
        public:
            HbLogServiceController() {
                qRegisterMetaType< hb::log::HbLogMessage >( "HbLogMessage" );
                mLogPoolThread = new QThread();
                mLogPool = new HbLoggerPool();
                mLogPool->moveToThread( mLogPoolThread );

                QObject::connect( mLogPoolThread, &QThread::started,
                                  mLogPool, &HbLoggerPool::running );
                mLogPoolThread->start();
            }

            ~HbLogServiceController() {
                mLogPoolThread->quit();
                mLogPoolThread->wait();
                delete mLogPool;
            }

            void install( const QString  & logPattern ) {
                qInstallMessageHandler(qtHbLogHandler);
                HbLogMessage::setPattern( logPattern );
            }

            void init()
            {
                if( !mLogManagers.hasLocalData() )
                {
                    HbLogManager * manager = q_check_ptr( new HbLogManager( mLogPool ) );
                    mLogManagers.setLocalData( manager );
                }
            }

            void processArgs( QStringList args )
            {
                for( QString arg: args ) {
                    HbLogArgumentParser parser;
                    parser.setInput( arg );

                    if ( parser.checkIsConsoleOutput() ) {
                        mLogPool->addConsoleOutput();
                    } else if ( parser.checkIsFileOutput() ) {
                        mLogPool->addFileOutput( parser.filePath(), parser.fileMaxSize() );
                    } else if ( parser.checkIsLocalOutput() ) {
                        mLogPool->addLocalSocketOutput( parser.serverName() );
                    } else if ( parser.checkIsTcpSocketOutput() ) {
                        mLogPool->addTcpSocketOutput( parser.ip(), parser.port() );
                    } else if ( parser.checkIsUdpSocketOutput() ) {
                        mLogPool->addUdpSocketOutput( parser.ip(), parser.port() );
                    } else if ( parser.checkIsLocalInput() ) {
                        mLogPool->addLocalSocketInput( parser.serverName() );
                    } else if ( parser.checkIsTcpSocketInput() ) {
                        mLogPool->addTcpSocketInput( parser.port() );
                    } else if ( parser.checkIsUdpSocketInput() ) {
                        mLogPool->addUdpSocketInput( parser.port() );
                    }
                }
            }

            void print( HbLogger::Level level, const HbLogContext & context, const QString & message )
            {
                logger()->print( level, context, message );
            }

            HbLoggerPool * pool() const
            {
                return mLogPool;
            }

            HbLogManager * logger()
            {
                init();
                return mLogManagers.localData();
            }

        private:
            QThreadStorage< HbLogManager * > mLogManagers;
            HbLoggerPool * mLogPool = nullptr;
            QThread* mLogPoolThread = nullptr;
        };
    }
}

Q_GLOBAL_STATIC( HbLogServiceController, logServiceController )

void HbLogService::install( const QString & logPattern )
{
    logServiceController()->install( logPattern );
}

void HbLogService::print( HbLogger::Level level, const HbLogContext & context, const QString & message )
{
    logServiceController()->print( level, context, message);
}

void HbLogService::processArgs( QStringList args )
{
    logServiceController()->processArgs( args );
}

void HbLogService::addUdpSocketInput( quint16 port )
{
    logServiceController()->pool()->addUdpSocketInput( port );
}

void HbLogService::addTcpSocketInput( quint16 port )
{
    logServiceController()->pool()->addTcpSocketInput( port );
}

void HbLogService::addLocalSocketInput( const QString & name )
{
    logServiceController()->pool()->addLocalSocketInput( name );
}

void HbLogService::addConsoleOutput()
{
    logServiceController()->pool()->addConsoleOutput();
}

void HbLogService::addGuiOutput( HbLogGuiNotifier * notifier )
{
    logServiceController()->pool()->addGuiOutput( notifier );
}

void HbLogService::addFileOutput( const QString & dir, quint32 max_size )
{
    logServiceController()->pool()->addFileOutput( dir, max_size );
}

void HbLogService::addUdpSocketOutput( const QString & ip, quint16 port )
{
    logServiceController()->pool()->addUdpSocketOutput( ip, port );
}

void HbLogService::addTcpSocketOutput( const QString & ip, quint16 port )
{
    logServiceController()->pool()->addTcpSocketOutput( ip, port );
}

void HbLogService::addLocalSocketOutput( const QString & name )
{
    logServiceController()->pool()->addLocalSocketOutput( name );
}
