/****************************************************************************
** Copyright (C) 2012-2015 Adrien Gavignet (hasboeuf)
** Contact: adrien.gavignet@gmail.com
**
** This file is part of the Hb module. Provided "AS IS", WITHOUT WARRANTIES
** OR CONDITIONS OF ANY KIND, either express or implied.
****************************************************************************/

#ifndef HBLOGTCPSOCKETINPUT_H
#define HBLOGTCPSOCKETINPUT_H

/*! \file HbLogTcpSocketInput.h */

// Qt
#include <QtNetwork/QTcpServer>
// Hb
#include <HbGlobal.h>
// Local
#include <inputs/HbLogAbstractInput.h>

namespace hb
{
    namespace log
    {
        class HbLogMessage;


        /*!
        * TODOC
        * \brief The %HbLogTcpSocketInput class defines a tcp server input.
        *
        * %HbLogTcpSocketInput inherits from HbLogAbstractInput.\n
        */
        class HbLogTcpSocketInput final : public QTcpServer, public HbLogAbstractInput
        {
            Q_OBJECT
            Q_DISABLE_COPY( HbLogTcpSocketInput )


        public:

            HbLogTcpSocketInput() = delete;
            HbLogTcpSocketInput( quint32 port );
            virtual ~HbLogTcpSocketInput();

            quint32 port() const;

        signals:

            void inputMessageReceived( HbLogMessage * message );

        private:

            void incomingConnection( qint32 descriptor );

        private callbacks:

            void onReadyRead();
            void onClientDisconnected();


        private:

            quint32 mPort;

            qint32 mAvailable;
            QSet< QTcpSocket * > mClients;
        };
    }
}

#endif

