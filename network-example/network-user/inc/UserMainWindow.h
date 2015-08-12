#ifndef USERMAINWINDOW_H
#define USERMAINWINDOW_H

// Qt
#include <QtCore/QHash>
#include <QtCore/QSortFilterProxyModel>
#include <QtGui/QStandardItemModel>
// Hb
#include <com/tcp/HbTcpClient.h>
#include <user/HbNetworkUserData.h>
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

        class ClientSumChannel;
        class ClientChatChannel;

        class UserMainWindow : public QMainWindow, private Ui::UserMainWindow
        {
            Q_OBJECT

        public:
            const qint32 PAGE_WELCOME = 0;
            const qint32 PAGE_AUTH    = 1;
            const qint32 PAGE_APP     = 2;

            explicit UserMainWindow( QWidget * parent = nullptr );
            virtual ~UserMainWindow();

        private:
            hb::network::HbClient * mpHbClient;
            ClientSumChannel      * mpSumChannel;
            ClientChatChannel     * mpChatChannel;

        private:

        public slots:
            void onClientStatusChanged( networkuid client_uid, HbNetworkProtocol::ClientStatus status );
            void onMeStatusChanged    ( HbNetworkProtocol::UserStatus status );

        private slots:
            void onStartClicked();
            void onStopClicked();
            void onSendClicked();
            void onComputeClicked();
            void onFacebookAuthRequest();
            void onFacebookUnauthRequest();

            // From chat channel
            void onChatUserJoined( const hb::network::HbNetworkUserData & user_data );
            void onChatUserLeft  ( const hb::network::HbNetworkUserData & user_data );
            void onChatMessageReceived( const QString & author, const QString & message );
            // From math channel
            void onComputationReceived( qint32 result );

        private:
            void resetGui();

        signals:

        };
    }
}

#endif // USERMAINWINDOW_H
