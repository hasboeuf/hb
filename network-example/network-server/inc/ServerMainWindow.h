#ifndef SERVERMAINWINDOW_H
#define SERVERMAINWINDOW_H

// Qt
#include <QtCore/QHash>
#include <QtCore/QSortFilterProxyModel>
#include <QtGui/QStandardItemModel>
// Hb
#include <com/tcp/HbTcpServer.h>
//#include <HbNetGlobal.h>
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

        class ServerMainWindow : public QMainWindow, private Ui::ServerMainWindow
        {
            Q_OBJECT

        public:
            explicit ServerMainWindow( QWidget * parent = nullptr );
            virtual ~ServerMainWindow();

        private slots:
            void onStartClicked();
            void onStopClicked ();

        private:
            hb::network::HbServer * mpHbServer;

        signals:

        };
    }
}

#endif // SERVERMAINWINDOW_H
