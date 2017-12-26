#ifndef HBLOGHANDLER_H
#define HBLOGHANDLER_H

// Qt
#include <QtCore/QObject>
#include <QtCore/QQueue>
// Hb
#include <native/HbLogEvent.h>


namespace hb {
    namespace log {

    #if !defined( HBLOGSERVICE_H )

        #define snSysDebug( message, ... )     emit sunset::sdk::log::HbLogHandler::handler()->print( \
            sunset::sdk::log::HbLogEvent( QtDebugMsg, __FILE__, __LINE__, Q_FUNC_INFO, QString().sprintf( message, ## __VA_ARGS__ ) ) )

        #define snSysWarning( message, ... )   emit sunset::sdk::log::HbLogHandler::handler()->print( \
            sunset::sdk::log::HbLogEvent( QtWarningMsg, QString().sprintf( message, ## __VA_ARGS__ ) ) )

        #define snSysError( message, ... )     emit sunset::sdk::log::HbLogHandler::handler()->print( \
            sunset::sdk::log::HbLogEvent( QtCriticalMsg, QString().sprintf( message, ## __VA_ARGS__ ) ) )

        #define snSysCritical( message, ... )  emit sunset::sdk::log::HbLogHandler::handler()->print( \
            sunset::sdk::log::HbLogEvent( QtFatalMsg, QString().sprintf( message, ## __VA_ARGS__ ) ) )

    #endif


        class HbLogHandler : public QObject
        {
            Q_OBJECT


        public :

            static HbLogHandler * handler();

            bool availables( QtMsgType type ) const;
            HbLogEvent dequeue( QtMsgType type );

        signals :

            void print( const HbLogEvent & event );
            void logEvent( QtMsgType type );

        private :

            HbLogHandler();
            virtual ~HbLogHandler() = default;

            void enqueue( const HbLogEvent & event );
            void connectNotify( const QMetaMethod & signal );


        private :

            QQueue< HbLogEvent > _debugs;
            QQueue< HbLogEvent > _warnings;
            QQueue< HbLogEvent > _errors;
            QQueue< HbLogEvent > _criticals;

            static HbLogHandler * _handler;
        };
    }
}

#endif // HBLOGHANDLER_H
