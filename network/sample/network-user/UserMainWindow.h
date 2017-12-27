#ifndef USERMAINWINDOW_H
#define USERMAINWINDOW_H

// Qt
#include <QtCore/QHash>
#include <QtCore/QSortFilterProxyModel>
#include <QtGui/QStandardItemModel>
// Hb
#include <com/tcp/HbTcpClient.h>
#include <user/HbNetworkUserInfo.h>
// Local
#include <ui_UserMainWindow.h>

namespace hb
{
    namespace network
    {
        class HbClient;
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

            static QString msClientId; // Shared by facebook and google => makes oauth exclusif in that sample.

        private:
            hb::network::HbClient * mpHbClient;
            ClientSumChannel      * mpSumChannel;
            ClientChatChannel     * mpChatChannel;

        private:

        public slots:
            void onClientStatusChanged( networkuid client_uid, HbNetworkProtocol::ClientStatus status );
            void onMeStatusChanged( HbNetworkProtocol::UserStatus status, hb::network::ShConstHbNetworkUserInfo me_info );

        private slots:
            void onStartClicked();
            void onStopClicked();
            void onSendClicked();
            void onComputeClicked();
            void onFacebookAuthRequest();
            void onGoogleAuthRequest();
            void onUnauthRequest();

            // From chat channel
            void onChatUserJoined( hb::network::ShConstHbNetworkUserInfo user_info );
            void onChatUserLeft  ( hb::network::ShConstHbNetworkUserInfo user_info );
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
