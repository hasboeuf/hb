#ifndef COMUSERMAINWINDOW_H
#define COMUSERMAINWINDOW_H

// Qt
// Hb
#include <tcp/HbTcpClient.h>
// Local
#include <ui_ComUserMainWindow.h>

namespace hb
{
    namespace comexample
    {

        class ComUserMainWindow : public QMainWindow, private Ui::ComUserMainWindow
        {
            Q_OBJECT

        public:
            explicit ComUserMainWindow(QWidget *parent = nullptr);
            virtual ~ComUserMainWindow() = default;

        private:
            hb::com::HbTcpClient mTcpClient;

        private slots:
            void onStartClicked();
            void onSendContractClicked();
            void onStopClicked();

            void onClientConnected       ( sockuid client_uid );
            void onClientDisconnected    ( sockuid client_uid );
            void onClientContractReceived( sockuid client_uid, const HbComContract * contract );

        signals:

        };
    }
}

#endif // COMUSERMAINWINDOW_H
