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

#include <HbLog.h>
#include <outputs/HbLogAbstractOutput.h>

#include <QFile>
#include <QTextStream>

namespace hb
{
    namespace log
    {
        /*!
        * TODOC
        * \brief The %HbLogFileOutput class defines a file output.
        *
        * %HbLogFileOutput inherits from HbLogAbstractOutput.\n
        */
        class HB_LOG_DECL HbLogFileOutput final : public HbLogAbstractOutput
        {
            Q_DISABLE_COPY( HbLogFileOutput )


        public:
            static const QString msDefaultPath;
            static const quint32 msMaxFileSize;

        public:

            HbLogFileOutput() = delete;
            HbLogFileOutput( const QString & path, quint32 max_size = 0, HbLogger::Levels level = HbLogger::LEVEL_ALL );
            virtual ~HbLogFileOutput();

            bool isValid() const;

        private:
            void closeLogFile();
            void createLogFile();
            void processMessage( const HbLogMessage & message );


        private:
            QString mPath;
            QFile mFile;
            quint32 mMaxSize;
            QTextStream mStream;
        };
    }
}

#endif
