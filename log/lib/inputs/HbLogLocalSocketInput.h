/****************************************************************************
** Copyright (C) 2012-2015 Adrien Gavignet (hasboeuf)
** Contact: adrien.gavignet@gmail.com
**
** This file is part of the Hb module. Provided "AS IS", WITHOUT WARRANTIES
** OR CONDITIONS OF ANY KIND, either express or implied.
****************************************************************************/

#ifndef HBLOGLOCALSOCKETINPUT_H
#define HBLOGLOCALSOCKETINPUT_H

/*! \file HbLogLocalSocketInput.h */

// Qt
#include <QtNetwork/QLocalServer>
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
        * \brief The %HbLogLocalSocketInput class defines a local server input.
        *
        * %HbLogLocalSocketInput inherits from HbLogAbstractInput.\n
        */
        class HbLogLocalSocketInput final : public QLocalServer, public HbLogAbstractInput
        {
            Q_OBJECT
            Q_DISABLE_COPY( HbLogLocalSocketInput )

        public:

            HbLogLocalSocketInput(const QString & name = QString() );
            virtual ~HbLogLocalSocketInput() = default;

            const QString & name() const;

        signals:

            void inputMessageReceived( HbLogMessage * message );

        private callbacks:

            void incomingConnection();
            void onReadyRead();
            void onClientDisconnected();


        private:
            QString mName;
            qint32 mExpected;
            QSet< QLocalSocket * > mClients;
        };
    }
}

#endif
