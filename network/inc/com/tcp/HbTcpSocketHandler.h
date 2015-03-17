#ifndef HBTCPSOCKETHANDLER_H
#define HBTCPSOCKETHANDLER_H

/*! \file HbTcpSocketHandler.h */

// Qt
#include <QtCore/QObject>
// Hb
#include <HbGlobal.h>
// Local
#include <com/HbSocketHandler.h>
#include <com/tcp/HbTcpServer.h> // Covariance.

namespace hb
{
    namespace network
    {
        class HbTcpSocket;

        /*!
         * TODOC
         */
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
