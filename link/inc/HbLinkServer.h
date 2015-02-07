#ifndef HBLINKSERVER_H
#define HBLINKSERVER_H

// Qt
#include <QtCore/QMap>
#include <QtCore/QString>
#include <QtNetwork/QTcpServer>

namespace hb
{
    namespace link
    {
        class HbLinkServer final: public QTcpServer
        {
            Q_OBJECT

        public:
            explicit HbLinkServer( QObject * parent = nullptr );
            ~HbLinkServer() = default;

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


#endif // HBLINKSERVER_H
