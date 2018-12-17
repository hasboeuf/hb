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
#include <LinkBrowserControls.h>
#include <facebook/HbFacebookRequester.h>
#include <google/HbGoogleRequester.h>
#include <ui_LinkMainWindow.h>

namespace hb {
namespace link {
class HbO2ClientFacebook;
class HbO2ServerFacebook;
class HbFacebookObject;

class HbO2ClientGoogle;
class HbO2ServerGoogle;
} // namespace link

namespace linkexample {

class LinkMainWindow : public QMainWindow, private Ui::LinkMainWindow {
    Q_OBJECT

public:
    explicit LinkMainWindow(QWidget* parent = nullptr);
    virtual ~LinkMainWindow();

    static QString msClientId;
    static QString msClientSecret;

private:
    void onFacebookClientLinkSucceed();
    void onFacebookServerLinkSucceed();
    void onFacebookRequestCompleted(quint64 request_id, hb::link::HbFacebookObject* object);

    void onGoogleClientLinkSucceed();
    void onGoogleServerLinkSucceed();
    void onGoogleRequestCompleted(quint64 request_id, hb::link::HbGoogleObject* object);

    void onFacebookConnectClicked();
    void onGoogleConnectClicked();

    hb::link::HbO2ClientFacebook* mFacebookClient;
    hb::link::HbO2ServerFacebook* mFacebookServer;
    hb::link::HbFacebookRequester mFacebookRequester;

    hb::link::HbO2ClientGoogle* mGoogleClient;
    hb::link::HbO2ServerGoogle* mGoogleServer;
    hb::link::HbGoogleRequester mGoogleRequester;

    LinkBrowserControls mBrowserControls;
};
} // namespace linkexample
} // namespace hb

#endif // USERMAINWINDOW_H
