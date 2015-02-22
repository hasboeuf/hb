#ifndef BASICNETWORKUSERMAINWINDOW_H
#define BASICNETWORKUSERMAINWINDOW_H

// Qt
// Hb
#include <com/tcp/HbTcpClient.h>
// Local
#include <ui_BasicUserMainWindow.h>

namespace hb
{
    namespace networkexample
    {

        class BasicUserMainWindow : public QMainWindow, private Ui::BasicUserMainWindow
        {
            Q_OBJECT

        public:
            explicit BasicUserMainWindow( QWidget *parent = nullptr );
            virtual ~BasicUserMainWindow() = default;

        private:
            hb::network::HbTcpClient mTcpClient;

        private slots:
            void onStartClicked();
            void onSendContractClicked();
            void onStopClicked();

            void onClientConnected       ( sockuid client_uid );
            void onClientDisconnected    ( sockuid client_uid );
            void onClientContractReceived( sockuid client_uid, const HbNetworkContract * contract );

        signals:

        };
    }
}

#endif // BASICNETWORKUSERMAINWINDOW_H
