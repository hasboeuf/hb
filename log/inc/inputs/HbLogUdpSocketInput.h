/****************************************************************************
** Copyright (C) 2012-2015 Adrien Gavignet (hasboeuf)
** Contact: adrien.gavignet@gmail.com
**
** This file is part of the Hb module. Provided "AS IS", WITHOUT WARRANTIES
** OR CONDITIONS OF ANY KIND, either express or implied.
****************************************************************************/

#ifndef HBLOGUDPSOCKETINPUT_H
#define HBLOGUDPSOCKETINPUT_H

/*! \file HbLogUdpSocketInput.h */

// Qt
#include <QtNetwork/QUdpSocket>
// Local
#include <inputs/HbLogAbstractInput.h>

namespace hb
{
    namespace log
    {
        class HbLogMessage;

        /*! 
        * TODOC
        */
        class HbLogUdpSocketInput final : public QUdpSocket, public HbLogAbstractInput
        {
            Q_OBJECT
            Q_DISABLE_COPY( HbLogUdpSocketInput )


        public:

            HbLogUdpSocketInput() = delete;
            HbLogUdpSocketInput( const QString & ip, quint32 port );
            virtual ~HbLogUdpSocketInput();

            const QString & ip() const;
            quint32 port() const;

        private:
            void onReconnection();

        signals:
            void inputMessageReceived( HbLogMessage * message );

        private callbacks:
            void onReadyRead();

        private:
            qint32  mExpected;
            QString mIp;
            quint32 mPort;
        };
    }
}

#endif // HBLOGUDPSOCKETINPUT_H
