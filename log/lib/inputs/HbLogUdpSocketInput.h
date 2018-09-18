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
#include <QtCore/QScopedPointer>
// Local
#include <inputs/HbLogAbstractInput.h>

class QUdpSocket;

namespace hb
{
    namespace log
    {
        class HbLogMessage;

        /*! 
        * TODOC
        */
        class HbLogUdpSocketInput final : public HbLogAbstractInput
        {
            Q_OBJECT
            Q_DISABLE_COPY( HbLogUdpSocketInput )

        public:

            HbLogUdpSocketInput() = delete;
            HbLogUdpSocketInput( quint16 port, QObject * parent = nullptr );
            virtual ~HbLogUdpSocketInput();

            quint16 port() const;

        protected:
            void init() override;

        private callbacks:
            void onReconnection();
            void onReadyRead();

        private:
            qint32  mExpected;
            quint16 mPort;
            QScopedPointer< QUdpSocket > mUdpSocket;
        };
    }
}

#endif // HBLOGUDPSOCKETINPUT_H
