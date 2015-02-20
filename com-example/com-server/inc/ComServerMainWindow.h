#ifndef COMSERVERMAINWINDOW_H
#define COMSERVERMAINWINDOW_H

// Qt
// Hb
#include <tcp/HbTcpServer.h>
// Local
#include <ui_ComServerMainWindow.h>

namespace hb
{
    namespace comexample
    {

        class ComServerMainWindow : public QMainWindow, private Ui::ComServerMainWindow
        {
            Q_OBJECT

        public:
            explicit ComServerMainWindow( QWidget * parent = nullptr );
            virtual ~ComServerMainWindow();

        private:
            hb::com::HbTcpServer mTcpServer;

        private slots:
            void onStartClicked();
            void onSendContractClicked();
            void onStopClicked();

            void onServerConnected       ( servuid server_uid );
            void onServerDisconnected    ( servuid server_uid );
            void onSocketConnected       ( servuid server_uid, sockuid socket_uid );
            void onSocketDisconnected    ( servuid server_uid, sockuid socket_uid );
            void onSocketContractReceived( servuid server_uid, sockuid socket_uid, const HbComContract * contract );

        signals:

        };
    }
}

#endif // COMSERVERMAINWINDOW_H
