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

// Qt
#include <QtCore/QScopedPointer>
// Hb
#include <outputs/HbLogAbstractOutput.h>

class QLocalSocket;

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
        class HbLogLocalSocketOutput final : public HbLogAbstractOutput
        {
            Q_OBJECT
            Q_DISABLE_COPY( HbLogLocalSocketOutput )

        public:
            HbLogLocalSocketOutput(const QString & name = QString(), QObject * parent = nullptr );
            virtual ~HbLogLocalSocketOutput();

            const QString & name() const;

        private:
            void processMessage( const HbLogMessagePtr & message ) override;
            void init() override;

        private slots:
            void onReconnection();

        private:
            QString mName;
            QScopedPointer< QLocalSocket > mLocalSocket;
        };
    }
}

#endif
