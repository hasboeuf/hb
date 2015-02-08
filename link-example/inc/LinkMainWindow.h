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
#include <HbLinkRequester.h>

class QNetworkAccessManager;

namespace hb
{
    namespace link
    {
        class HbO2ClientFacebook;
        class HbO2ServerFacebook;
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
            hb::link::HbLinkRequester      mRequester;

        public slots:
            void onOpenBrower( const QUrl & url );
            void onClientLinkSucceed();
            void onServerLinkSucceed();
            void onRequestFinished( quint64 request_id, const QJsonDocument & doc );
            void onRequestError   ( quint64 request_id, const QString & error );

        private slots:
            void onConnectClicked();

        signals:

        };
    }
}

#endif // USERMAINWINDOW_H
