// Qt
#include <QtCore/QCoreApplication>
#include <QtCore/QThread>
// Hb
#include <HbLogService.h>
#include <HbLogManager.h>
#include <HbLogMessage.h>
#include <HbLoggerPool.h>

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

            void processArgs(QStringList args)
            {
                QRegExp check("-hblog-(output|input)-(local|tcp|udp|file):");

                // Required args number.
                static const quint32 ARG_NB_REQUIRED_FILE       = 2;
                static const quint32 ARG_NB_REQUIRED_LOCAL      = 1;
                static const quint32 ARG_NB_REQUIRED_INPUT_TCP  = 1;
                static const quint32 ARG_NB_REQUIRED_OUTPUT_TCP = 2;
                static const quint32 ARG_NB_REQUIRED_INPUT_UDP  = 2;
                static const quint32 ARG_NB_REQUIRED_OUTPUT_UDP = 1;
                // Local arg positions.
                static const quint32 ARG_POS_LOCAL_NAME = 0;
                // Ip arg positions.
                static const quint32 ARG_POS_PORT = 0;
                static const quint32 ARG_POS_IP   = 1;
                // File arg positions.
                static const quint32 ARG_POS_FILE_DIR = 0;
                static const quint32 ARG_POS_FILE_MAX_SIZE = 1;

                QString error;

                for( QString arg: args )
                {
                    int pos = check.indexIn( arg );
                    if(pos != -1)
                    {
                        QString inout = check.cap(1);
                        QString type = check.cap(2);

                        QStringList parameters = arg.split(":", QString::SkipEmptyParts);
                        if(parameters.size() < 2)
                        {
                            break;
                        }
                        parameters.removeAt(0); // Remove -hblog-(output|input)-(local|tcp|file) entry.

                        quint32 nb_parameters = parameters.size();


                        if( type == "file" && nb_parameters == ARG_NB_REQUIRED_FILE )
                        {
                            bool is_valid_size = false;

                            quint32 file_max_size = parameters.at( ARG_POS_FILE_MAX_SIZE ).toInt( &is_valid_size );

                            if ( is_valid_size )
                            {
                                QString dir_name = parameters.at(ARG_POS_FILE_DIR);

                                if( mLogPool->addFileOutput( dir_name, file_max_size, &error ) == 0 )
                                {
                                    qDebug() << "HbLog error: " + error;
                                    error.clear();
                                }
                            }
                        }
                        else if( type == "local" && nb_parameters == ARG_NB_REQUIRED_LOCAL )
                        {
                            QString local_address = parameters.at( ARG_POS_LOCAL_NAME );

                            if( inout == "input" )
                            {
                                if( mLogPool->addLocalSocketInput( local_address, &error ) == 0 )
                                {
                                    qDebug() << "HbLog error: " + error;
                                    error.clear();
                                }
                            }
                            else // output
                            {
                                if( mLogPool->addLocalSocketOutput( local_address, &error ) == 0 )
                                {
                                    qDebug() << "HbLog error: " + error;
                                    error.clear();
                                }
                            }
                        }
                        else if( type == "udp" )
                        {
                            if ( inout == "input" && nb_parameters == ARG_NB_REQUIRED_INPUT_UDP )
                            {
                                bool is_valid_port = false;
                                quint32 port = parameters.at( ARG_POS_PORT ).toInt( &is_valid_port );

                                if ( is_valid_port )
                                {
                                    QString ip = parameters.at( ARG_POS_IP );
                                    if( mLogPool->addUdpSocketInput( ip, port, &error ) == 0 )
                                    {
                                        qDebug() << "HbLog error: " + error;
                                        error.clear();
                                    }
                                }
                            }
                            else if( inout == "output" && nb_parameters == ARG_NB_REQUIRED_OUTPUT_UDP )
                            {
                                bool is_valid_port = false;
                                quint32 port = parameters.at( ARG_POS_PORT ).toInt( &is_valid_port );

                                if ( is_valid_port )
                                {
                                    if( mLogPool->addUdpSocketOutput( "todo", port, &error ) == 0 )
                                    {
                                        qDebug() << "HbLog error: " + error;
                                        error.clear();
                                    }
                                }
                            }
                        }
                        else // Tcp
                        {
                            if ( inout == "input" && nb_parameters == ARG_NB_REQUIRED_INPUT_TCP )
                            {
                                bool is_valid_port = false;
                                quint32 port = parameters.at(ARG_POS_PORT).toInt(&is_valid_port);

                                if (is_valid_port)
                                {
                                    if( mLogPool->addTcpSocketInput( port, &error ) == 0 )
                                    {
                                        qDebug() << "HbLog error: " + error;
                                        error.clear();
                                    }
                                }
                            }
                            else if (inout == "output" && nb_parameters == ARG_NB_REQUIRED_OUTPUT_TCP)
                            {
                                bool is_valid_port = false;
                                quint32 port = parameters.at(ARG_POS_PORT).toInt(&is_valid_port);

                                if (is_valid_port)
                                {
                                    QString ip = parameters.at(ARG_POS_IP);
                                    if( mLogPool->addTcpSocketOutput( ip, port, &error ) == 0 )
                                    {
                                        qDebug() << "HbLog error: " + error;
                                        error.clear();
                                    }
                                }
                            }
                        }
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

loguid HbLogService::addUdpSocketInput( const QString & ip, quint16 port, QString * error )
{
    return logServiceController()->pool()->addUdpSocketInput( ip, port, error );
}

loguid HbLogService::addTcpSocketInput( quint16 port, QString * error )
{
    return logServiceController()->pool()->addTcpSocketInput( port, error );
}

loguid HbLogService::addLocalSocketInput( const QString & name, QString * error )
{
    return logServiceController()->pool()->addLocalSocketInput( name, error );
}

bool HbLogService::removeInput( loguid uid, QString * error )
{
    return logServiceController()->pool()->removeInput( uid, error );
}

loguid HbLogService::addConsoleOutput( QString * error )
{
    return logServiceController()->pool()->addConsoleOutput( error );
}

loguid HbLogService::addGuiOutput( HbLogGuiNotifier * notifier, QString * error )
{
    return logServiceController()->pool()->addGuiOutput( notifier, error );
}

loguid HbLogService::addFileOutput( const QString & dir, quint32 max_size, QString * error )
{
    return logServiceController()->pool()->addFileOutput( dir, max_size, error );
}

loguid HbLogService::addUdpSocketOutput( const QString & ip, quint16 port, QString * error )
{
    return logServiceController()->pool()->addUdpSocketOutput( ip, port, error );
}

loguid HbLogService::addTcpSocketOutput( const QString & ip, quint16 port, QString * error )
{
    return logServiceController()->pool()->addTcpSocketOutput( ip, port, error );
}

loguid HbLogService::addLocalSocketOutput( const QString & name, QString * error )
{
    return logServiceController()->pool()->addLocalSocketOutput( name, error );
}

bool HbLogService::removeOutput( loguid uid, QString * error )
{
    return logServiceController()->pool()->removeOutput( uid, error );
}
