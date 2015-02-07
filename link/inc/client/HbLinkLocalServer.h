#ifndef HBLINKLOCALSERVER_H
#define HBLINKLOCALSERVER_H

// Qt
#include <QtCore/QMap>
#include <QtCore/QString>
#include <QtNetwork/QTcpServer>
// Hb
#include <HbLink.h>

namespace hb
{
    namespace link
    {
        class HB_LINK_DECL HbLinkLocalServer final: public QTcpServer
        {
            Q_OBJECT

        public:
            explicit HbLinkLocalServer( QObject * parent = nullptr );
            ~HbLinkLocalServer() = default;

        signals:
            void responseReceived( QHash< QString, QString > response );

        public slots:
            void onIncomingConnection();
            void onReadyRead();

        private:
            QHash< QString, QString > parseResponse( QByteArray & data );
        };
    }
}


#endif // HBLINKLOCALSERVER_H
