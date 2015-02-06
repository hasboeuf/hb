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
            void parametersReceived( QMap< QString, QString > parameters );

        public slots:
            void onIncomingConnection();
            void onReadyRead();

        private:
            QMap<QString, QString> parseQueryParameters( QByteArray & data );
        };
    }
}


#endif // HBLINKSERVER_H
