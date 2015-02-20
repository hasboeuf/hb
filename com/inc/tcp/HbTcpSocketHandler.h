#ifndef HBTCPSOCKETHANDLER_H
#define HBTCPSOCKETHANDLER_H

// Qt
#include <QtCore/QObject>
// Hb
#include <HbGlobal.h>
// Local
#include <HbSocketHandler.h>
#include <tcp/HbTcpServer.h> // Covariance.

namespace hb
{
    namespace com
    {
        class HbTcpSocket;

        class HbTcpSocketHandler : public HbSocketHandler
        {
            Q_OBJECT
            Q_DISABLE_COPY( HbTcpSocketHandler )
            Q_FRIEND_CLASS( HbTcpServer )

        protected:

            HbTcpSocketHandler( HbTcpServer * server );
            virtual ~HbTcpSocketHandler();

            virtual HbTcpServer * server( ) const;

            virtual void init();
            virtual void reset();

        public slots:
            virtual void onNewPendingConnection( qint32 socket_descriptor );

        private:
            HbTcpServer * mpServer;

        signals:

        };
    }
}

#endif // HBTCPSOCKETHANDLER_H
