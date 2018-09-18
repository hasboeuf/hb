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
#include <HbLog.h>
#include <core/HbUid.h>
// Local

namespace hb
{
    namespace log
    {
        /*!
         * TODOC.
         */
        class HbLogAbstractOutput : public QObject, public HbUid< CLASS_LOG >
        {
            Q_DISABLE_COPY( HbLogAbstractOutput )
            friend class HbLoggerPool;

        public:
            HbLogAbstractOutput( QObject * parent = nullptr );
            virtual ~HbLogAbstractOutput() = default;

        protected:
            virtual void init() = 0;
            virtual void processMessage( const HbLogMessagePtr & message ) = 0;
        };
    }
}

#endif // HBLOGABSTRACTOUTPUT_H
