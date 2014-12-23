#ifndef HBTCPSOCKETHANDLER_H
#define HBTCPSOCKETHANDLER_H

// Qt
#include <QtCore/QObject>
// Hb
#include <HbGlobal.h>
// Local
#include <HbSocketHandler.h>

namespace hb
{
	namespace network
    {
		class HbTcpSocket;
		class HbTcpServer;

        class HbTcpSocketHandler : public HbSocketHandler
        {
			Q_OBJECT
			Q_DISABLE_COPY( HbTcpSocketHandler )
			Q_FRIEND_CLASS( HbTcpServer )

        protected:

			HbTcpSocketHandler( HbTcpServer * server );
            virtual ~HbTcpSocketHandler();

			virtual void init();

        public slots:
			virtual void onNewPendingConnection( qint32 socket_descriptor );

		private:

        signals:

        };
    }
}

#endif // HBTCPSOCKETHANDLER_H
