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
#include <QtCore/QScopedPointer>
#include <QtCore/QSet>
// Hb
#include <HbGlobal.h>
// Local
#include <inputs/HbLogAbstractInput.h>

class QLocalSocket;
class QLocalServer;

namespace hb
{
    namespace log
    {
        class HbLogMessage;

        /*!
        * TODOC
        * \brief The %HbLogLocalSocketInput class defines a local server input.
        */
        class HbLogLocalSocketInput final : public HbLogAbstractInput
        {
            Q_OBJECT
            Q_DISABLE_COPY( HbLogLocalSocketInput )

        public:
            HbLogLocalSocketInput( const QString & name = QString(), QObject * parent = nullptr );
            ~HbLogLocalSocketInput() override;

            const QString & name() const;

        protected:
            void init() override;

        private callbacks:
            void incomingConnection();
            void onReadyRead();
            void onClientDisconnected();

        private:
            QString mName;
            qint32 mExpected;
            QScopedPointer< QLocalServer > mLocalServer;
            QSet< QLocalSocket * > mClients;
        };
    }
}

#endif

