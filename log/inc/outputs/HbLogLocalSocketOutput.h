/****************************************************************************
** Copyright (C) 2012-2015 Adrien Gavignet (hasboeuf)
** Contact: adrien.gavignet@gmail.com
**
** This file is part of the Hb module. Provided "AS IS", WITHOUT WARRANTIES
** OR CONDITIONS OF ANY KIND, either express or implied.
****************************************************************************/

#ifndef HBLOGLOCALSOCKETOUTPUT_H
#define HBLOGLOCALSOCKETOUTPUT_H

/*! \file HbLogLocalSocketOutput.h */

#include <outputs/HbLogAbstractOutput.h>

#include <QLocalSocket>

namespace hb
{
    namespace log
    {
        /*! 
        * TODOC
        * \brief The %HbLogLocalSocketOutput class defines a local socket output.
        *
        * %HbLogLocalSocketOutput inherits from HbLogAbstractOutput.\n
        */
        class HbLogLocalSocketOutput final : public QLocalSocket, public HbLogAbstractOutput
        {
            Q_OBJECT
            Q_DISABLE_COPY( HbLogLocalSocketOutput )

        private:
            QString mName;

        public:

            HbLogLocalSocketOutput( const QString & name = QString(), HbLogger::Levels level = HbLogger::LEVEL_ALL );
            virtual ~HbLogLocalSocketOutput();
                
            bool isValid() const;

        private:

            void processMessage( const HbLogMessage & message );

        private slots:

            void onReconnection();
            void onDisconnected();
        };
    }
}

#endif
