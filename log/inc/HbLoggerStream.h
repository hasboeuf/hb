/****************************************************************************
** Copyright (C) 2012-2015 Adrien Gavignet (hasboeuf)
** Contact: adrien.gavignet@gmail.com
**
** This file is part of the Hb module. Provided "AS IS", WITHOUT WARRANTIES
** OR CONDITIONS OF ANY KIND, either express or implied.
****************************************************************************/

#ifndef HBLOGGERSTREAM_H
#define HBLOGGERSTREAM_H

/*! \file HbLoggerStream.h */

// Qt
#include <QtCore/QObject>
#include <QtCore/QSet>
// Hb
#include <core/HbEnum.h>
#include <HbLog.h>


namespace hb
{
    namespace log
    {

        class HbLogManager;


        /*!
         * Internal class, TODOC.
         */
        class HB_LOG_DECL HbLoggerStream : public QObject
        {
            Q_OBJECT
            Q_DISABLE_COPY(HbLoggerStream)
            Q_ENUMS_HANDLER( HbLoggerStream )
            Q_ENUMS( State )

        public :
            static const char * DEFAULT_LOCAL_SERVER_NAME;

            enum State : quint16
            {
                INOUT_ADD_SUCCESS             = 0,
                INOUT_WRONG_PARAMETERS,
                INOUT_ALREADY_EXISTS,
                INOUT_CONSOLE_ALREADY_EXISTS, // Specific to Output.
                INOUT_DEL_SUCCESS,
                INOUT_DEL_FAIL
            };
            Q_META_ENUMS( State )

        protected :

            HbLoggerStream() = delete;
            HbLoggerStream( HbLogManager * parent );
            virtual ~HbLoggerStream() = default;

        };
    }
}

Q_DECLARE_METATYPE( hb::log::HbLoggerStream::State )

#endif // HBLOGGERSTREAM_H
