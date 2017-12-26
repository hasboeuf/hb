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
#include <google/HbGoogleRequester.h>
#include <LinkBrowserControls.h>

namespace hb
{
    namespace link
    {
        class HbO2ClientFacebook;
        class HbO2ServerFacebook;
        class HbFacebookObject;

        class HbO2ClientGoogle;
        class HbO2ServerGoogle;
    }

    namespace linkexample
    {

        class LinkMainWindow : public QMainWindow, private Ui::LinkMainWindow
        {
            Q_OBJECT

        public:
            explicit LinkMainWindow(QWidget * parent = nullptr);
            virtual ~LinkMainWindow();

            static QString msClientId;
            static QString msClientSecret;

        private:
            hb::link::HbO2ClientFacebook * mpFacebookClient;
            hb::link::HbO2ServerFacebook * mpFacebookServer;
            hb::link::HbFacebookRequester  mFacebookRequester;

            hb::link::HbO2ClientGoogle * mpGoogleClient;
            hb::link::HbO2ServerGoogle * mpGoogleServer;
            hb::link::HbGoogleRequester  mGoogleRequester;

            LinkBrowserControls mBrowserControls;

        public slots:
            void onFacebookClientLinkSucceed();
            void onFacebookServerLinkSucceed();
            void onFacebookRequestCompleted(quint64 request_id, hb::link::HbFacebookObject * object );

            void onGoogleClientLinkSucceed();
            void onGoogleServerLinkSucceed();
            void onGoogleRequestCompleted( quint64 request_id, hb::link::HbGoogleObject * object );

        private slots:
            void onFacebookConnectClicked();
            void onGoogleConnectClicked();

        signals:

        };
    }
}

#endif // USERMAINWINDOW_H
