#ifndef USERMAINWINDOW_H
#define USERMAINWINDOW_H

// Qt
#include <QtCore/QHash>
#include <QtCore/QSortFilterProxyModel>
#include <QtGui/QStandardItemModel>
// Hb
//#include <HbNetGlobal.h>
#include <tcp/HbTcpClient.h>
// Local
#include <ui_UserMainWindow.h>

namespace hb
{
    namespace network
    {
        //class HbTcpClient;
    }

	namespace log
	{
		class HbLogWidget;
	}

    namespace networkexample
    {

        class UserMainWindow : public QMainWindow, private Ui::UserMainWindow
        {
            Q_OBJECT

        public:
            explicit UserMainWindow(QWidget *parent = 0);
            virtual ~UserMainWindow();

        private:
            // Logger
            hb::log::HbLogWidget* mpLogWidget;
            // Network
            hb::network::HbTcpClient mTcpClient;

            bool mStarted;

        private:
            void init();

        public slots:
            void showLogs(bool visible);
            void onClientConnected();
            void onClientDisconnected();

        private slots:
            void onStartClicked();

        signals:

        };
    }
}

#endif // USERMAINWINDOW_H
