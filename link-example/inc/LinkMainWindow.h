#ifndef USERMAINWINDOW_H
#define USERMAINWINDOW_H

// Qt
#include <QtCore/QHash>
#include <QtCore/QSortFilterProxyModel>
#include <QtGui/QStandardItemModel>
#include <QtNetwork/QNetworkAccessManager>
// Hb

// Local
#include <ui_LinkMainWindow.h>

class QNetworkAccessManager;

namespace hb
{
    namespace link
    {
        class HbO2Facebook;
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
            hb::link::HbO2Facebook * mpO2;
            QNetworkAccessManager mNetworkAccess;

        public slots:
            void onOpenBrower( const QUrl & url );

        private slots:
            void onConnectClicked();
            void onNetworkAccessFinished( QNetworkReply * reply );

        signals:

        };
    }
}

#endif // USERMAINWINDOW_H
