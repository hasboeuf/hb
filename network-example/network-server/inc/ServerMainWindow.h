#ifndef SERVERMAINWINDOW_H
#define SERVERMAINWINDOW_H

// Qt
#include <QtCore/QHash>
#include <QtCore/QSortFilterProxyModel>
#include <QtGui/QStandardItemModel>
// Hb
#include <com/tcp/HbTcpServer.h>
// Local
#include <ui_ServerMainWindow.h>

namespace hb
{
    namespace network
    {
        class HbServer;
    }

    namespace log
    {
        class HbLogWidget;
    }

    namespace networkexample
    {
        class ServerSumChannel;
        class ServerChatChannel;

        class ServerMainWindow : public QMainWindow, private Ui::ServerMainWindow
        {
            Q_OBJECT

        public:
            explicit ServerMainWindow( QWidget * parent = nullptr );
            virtual ~ServerMainWindow();

            static QString msClientId;     // Shared by facebook and google => makes oauth exclusif in that sample.
            static QString msClientSecret; // Shared by facebook and google => makes oauth exclusif in that sample.

        public slots:
            void onServerStatusChanged( networkuid server_uid, HbNetworkProtocol::ServerStatus status );

        private slots:
            void onStartClicked();
            void onStopClicked ();

        private:
            hb::network::HbServer * mpHbServer;
            ServerSumChannel      * mpSumChannel;
            ServerChatChannel     * mpChatChannel;

        signals:

        };
    }
}

#endif // SERVERMAINWINDOW_H
