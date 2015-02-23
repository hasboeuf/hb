#ifndef USERMAINWINDOW_H
#define USERMAINWINDOW_H

// Qt
#include <QtCore/QHash>
#include <QtCore/QSortFilterProxyModel>
#include <QtGui/QStandardItemModel>
// Hb
//#include <HbNetGlobal.h>
#include <com/tcp/HbTcpClient.h>
// Local
#include <ui_UserMainWindow.h>

namespace hb
{
    namespace network
    {
        class HbClient;
    }

    namespace log
    {
        class HbLogWidget;
    }

    namespace link
    {
        class HbO2ClientFacebook;
    }

    namespace networkexample
    {

        class UserMainWindow : public QMainWindow, private Ui::UserMainWindow
        {
            Q_OBJECT

        public:
            explicit UserMainWindow( QWidget * parent = nullptr );
            virtual ~UserMainWindow();

        private:
            hb::network::HbClient * mpHbClient;
            hb::link::HbO2ClientFacebook * mpFacebookClient;

        private:
            void init();

        public slots:
            void onClientStatusChanged( networkuid client_uid, HbNetworkProtocol::ClientStatus status );
            void onMeStatusChanged    ( HbNetworkProtocol::UserStatus status );

        private slots:
            void onStartClicked();
            void onStopClicked();
            void onUserConnectionRequest();
            void onFacebookConnectionRequest();
            void onFacebookOpenBrower( const QUrl & url );
            void onFacebookLinked();

        signals:

        };
    }
}

#endif // USERMAINWINDOW_H
