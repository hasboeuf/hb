#ifndef BASICNETWORKSERVERMAINWINDOW_H
#define BASICNETWORKSERVERMAINWINDOW_H

// Qt
// Hb
#include <com/tcp/HbTcpServer.h>
// Local
#include <ui_BasicServerMainWindow.h>

namespace hb
{
    namespace networkexample
    {

        class BasicServerMainWindow : public QMainWindow, private Ui::BasicServerMainWindow
        {
            Q_OBJECT

        public:
            explicit BasicServerMainWindow( QWidget * parent = nullptr );
            virtual ~BasicServerMainWindow() = default;

        private:
            hb::network::HbTcpServer mTcpServer;

        private slots:
            void onStartClicked();
            void onSendContractClicked();
            void onStopClicked();

            void onServerConnected       ( servuid server_uid );
            void onServerDisconnected    ( servuid server_uid );
            void onSocketConnected       ( servuid server_uid, sockuid socket_uid );
            void onSocketDisconnected    ( servuid server_uid, sockuid socket_uid );
            void onSocketContractReceived( servuid server_uid, sockuid socket_uid, const HbNetworkContract * contract );

        signals:

        };
    }
}

#endif // BASICNETWORKSERVERMAINWINDOW_H
