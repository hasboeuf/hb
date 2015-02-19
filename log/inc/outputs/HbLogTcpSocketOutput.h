/****************************************************************************
** Copyright (C) 2012-2015 Adrien Gavignet (hasboeuf)
** Contact: adrien.gavignet@gmail.com
**
** This file is part of the Hb module. Provided "AS IS", WITHOUT WARRANTIES
** OR CONDITIONS OF ANY KIND, either express or implied.
****************************************************************************/

#ifndef HBLOGTCPSOCKETOUTPUT_H
#define HBLOGTCPSOCKETOUTPUT_H

/*! \file HbLogTcpSocketOutput.h */

#include <outputs/HbLogAbstractOutput.h>

#include <QTcpSocket>

namespace hb
{
    namespace log
    {
        /*! \namespace hb::log */


        /*! 
        * \class HbLogTcpSocketOutput
        * \brief The %HbLogTcpSocketOutput class defines a tcp socket output.
        *
        * %HbLogTcpSocketOutput inherits from HbLogAbstractOutput.\n
        */
        class HbLogTcpSocketOutput final : public QTcpSocket, public HbLogAbstractOutput
        {
            Q_OBJECT
            Q_DISABLE_COPY( HbLogTcpSocketOutput )


        public :

            HbLogTcpSocketOutput() = delete;
            HbLogTcpSocketOutput( const QString & ip, quint32 port, HbLogger::Levels level = HbLogger::LEVEL_ALL );
            virtual ~HbLogTcpSocketOutput();

            bool isValid() const;

            const QString & ip() const;
            quint32 port() const;

        private :

            void processMessage( const HbLogMessage & message );

        private slots :

            void onReconnection();
            void onDisconnected();


        private :

            QString mIp;
            quint32 mPort;
        };
    }
}

#endif
