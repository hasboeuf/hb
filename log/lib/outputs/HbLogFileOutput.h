/****************************************************************************
** Copyright (C) 2012-2015 Adrien Gavignet (hasboeuf)
** Contact: adrien.gavignet@gmail.com
**
** This file is part of the Hb module. Provided "AS IS", WITHOUT WARRANTIES
** OR CONDITIONS OF ANY KIND, either express or implied.
****************************************************************************/

#ifndef HBLOGFILEOUTPUT_H
#define HBLOGFILEOUTPUT_H

/*! \file HbLogFileOutput.h */

// Qt
#include <QtCore/QScopedPointer>
// Hb
#include <HbLog.h>
#include <outputs/HbLogAbstractOutput.h>

class QFile;
class QTextStream;

namespace hb
{
    namespace log
    {
        /*!
        * \brief The %HbLogFileOutput class defines a file output.
        */
        class HB_LOG_DECL HbLogFileOutput final : public HbLogAbstractOutput
        {
            Q_DISABLE_COPY( HbLogFileOutput )

        public:
            static const QString msDefaultPath;
            static const quint32 msMaxFileSize;

        public:
            HbLogFileOutput() = delete;
            HbLogFileOutput( const QString & path, quint32 maxSize = 0, QObject * parent = nullptr );
            virtual ~HbLogFileOutput();

        protected:
            void init() override;
            void processMessage( const HbLogMessagePtr & message ) override;

        private:
            void closeLogFile();
            void createLogFile();

        private:
            QString mPath;
            quint32 mMaxSize;
            QScopedPointer< QFile > mFile;
            QScopedPointer< QTextStream > mStream;
        };
    }
}

#endif
