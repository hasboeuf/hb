#ifndef USERMAINWINDOW_H
#define USERMAINWINDOW_H

// Qt
#include <QtCore/QHash>
#include <QtCore/QJsonDocument>
#include <QtCore/QSortFilterProxyModel>
#include <QtGui/QStandardItemModel>
#include <QtNetwork/QNetworkAccessManager>
// Hb

// Local
#include <ui_LinkMainWindow.h>
#include <facebook/HbFacebookRequester.h>

class QNetworkAccessManager;

namespace hb
{
    namespace link
    {
        class HbO2ClientFacebook;
        class HbO2ServerFacebook;
        class HbFacebookObject;
    }

    namespace linkexample
    {

        class LinkMainWindow : public QMainWindow, private Ui::LinkMainWindow
        {
            Q_OBJECT

        public:
            explicit LinkMainWindow(QWidget * parent = nullptr);
            virtual ~LinkMainWindow();

        private:
            hb::link::HbO2ClientFacebook * mpFacebookClient;
            hb::link::HbO2ServerFacebook * mpFacebookServer;
            hb::link::HbFacebookRequester  mRequester;

        public slots:
            void onOpenBrower( const QUrl & url );
            void onClientLinkSucceed();
            void onServerLinkSucceed();
            void onRequestCompleted( hb::link::HbFacebookObject * object );

        private slots:
            void onConnectClicked();

        signals:

        };
    }
}

#endif // USERMAINWINDOW_H
