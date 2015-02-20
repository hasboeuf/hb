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
            virtual ~ComUserMainWindow();

        private:
            hb::com::HbTcpClient mTcpClient;

        public slots:
            void onClientConnected();
            void onClientDisconnected();

        private slots:
            void onStartClicked();
            void onStopClicked();

        signals:

        };
    }
}

#endif // COMUSERMAINWINDOW_H
