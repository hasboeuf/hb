/****************************************************************************
** Copyright (C) 2012-2015 Adrien Gavignet (hasboeuf)
** Contact: adrien.gavignet@gmail.com
**
** This file is part of the Hb module. Provided "AS IS", WITHOUT WARRANTIES
** OR CONDITIONS OF ANY KIND, either express or implied.
****************************************************************************/

#ifndef HBLOGABSTRACTOUTPUT_H
#define HBLOGABSTRACTOUTPUT_H

/*! \file HbLogAbstractOutput.h */

// Hb
#include <core/HbUid.h>
// Local
#include <IHbLoggerOutput.h>

class QMutex;

namespace hb
{
    namespace log
    {

        class HbLogMessage;

        /*!
         * TODOC.
         */
        class HbLogAbstractOutput :
            public IHbLoggerOutput,
            public HbUid< CLASS_LOG >
        {
            Q_DISABLE_COPY( HbLogAbstractOutput )


        public:

            virtual ~HbLogAbstractOutput();

            virtual OutputType type() const final;
            virtual bool isValid() const;

            virtual void setLevel( HbLogger::Levels level ) final;
            virtual HbLogger::Levels level() const final;

            virtual void processMessage( const HbLogMessage & message ) = 0;

        protected:

            HbLogAbstractOutput() = default;
            HbLogAbstractOutput( OutputType type, HbLogger::Levels level );


        private:

            QMutex * mpMutex;

            OutputType mType;
            HbLogger::Levels mLevel;
        };
    }
}

#endif // HBLOGABSTRACTOUTPUT_H
