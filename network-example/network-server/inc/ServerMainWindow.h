#ifndef SERVERMAINWINDOW_H
#define SERVERMAINWINDOW_H

// Qt
#include <QtCore/QHash>
#include <QtCore/QSortFilterProxyModel>
#include <QtGui/QStandardItemModel>
// Hb
//#include <HbNetGlobal.h>
// Local
#include <ui_ServerMainWindow.h>

namespace hb
{
    namespace network
    {
		class HbTcpServer;
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
            explicit ServerMainWindow(QWidget *parent = 0);
            virtual ~ServerMainWindow();

        private:

            // Logger
            hb::log::HbLogWidget* mpLogWidget;

            // Network
            hb::network::HbTcpServer* mpTcpServer;

        private:
            void init();

        public slots:
            void showLogs(bool visible);

        private slots:
            void onStartClicked();

        signals:

        };
    }
}

#endif // SERVERMAINWINDOW_H
