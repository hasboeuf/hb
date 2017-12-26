/****************************************************************************
** Copyright (C) 2012-2015 Adrien Gavignet (hasboeuf)
** Contact: adrien.gavignet@gmail.com
**
** This file is part of the Hb module. Provided "AS IS", WITHOUT WARRANTIES
** OR CONDITIONS OF ANY KIND, either express or implied.
****************************************************************************/

#ifndef HBLOGUDPSOCKETOUTPUT_H
#define HBLOGUDPSOCKETOUTPUT_H

/*! \file HbLogTcpSocketInput.h */

// Qt
#include <QtNetwork/QUdpSocket>
// Hb
#include <HbGlobal.h>
// Local
#include <outputs/HbLogAbstractOutput.h>

namespace hb
{
    namespace log
    {
        class HbLogMessage;


        /*!
        * TODOC
        */
        class HbLogUdpSocketOutput final : public QUdpSocket, public HbLogAbstractOutput
        {
            Q_OBJECT
            Q_DISABLE_COPY( HbLogUdpSocketOutput )


        public:

            HbLogUdpSocketOutput() = delete;
            HbLogUdpSocketOutput( quint32 port, HbLogger::Levels level = HbLogger::LEVEL_ALL );
            virtual ~HbLogUdpSocketOutput();

            quint32 port() const;

        private:

            void processMessage( const HbLogMessage & message );

        private:
            quint32 mPort;
        };
    }
}

#endif // HBLOGUDPSOCKETOUTPUT_H

