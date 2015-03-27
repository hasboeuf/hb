/****************************************************************************
** Copyright (C) 2012-2015 Adrien Gavignet (hasboeuf)
** Contact: adrien.gavignet@gmail.com
**
** This file is part of the Hb module. Provided "AS IS", WITHOUT WARRANTIES
** OR CONDITIONS OF ANY KIND, either express or implied.
****************************************************************************/

#ifndef HBLOGCONTEXT_H
#define HBLOGCONTEXT_H

/*! \file HbLogContext.h */

// Hb
#include <HbLogger.h>

namespace hb
{
    namespace log
    {
        /*!
         * HbLogContext represents the exact place of a log trace in the code.
         * Internal class.
         */
        class HB_LOG_DECL HbLogContext final
        {
        public :

            HbLogContext();
            HbLogContext( const HbLogContext & context );
            HbLogContext( const char * file, qint32 line, const char * function );
            HbLogContext( const QString & owner, const char * file, qint32 line, const char * function );
            virtual ~HbLogContext() = default;

            HbLogContext & operator =( const HbLogContext & context );

            const QString & owner   () const;
            const QString & file    () const;
            qint32          line    () const;
            const QString & function() const;

            void print ( HbLogger::Level level, const char * message, ... ) const;
            void system( HbLogger::Level level, const char * message, ... ) const;

            friend QDataStream & operator <<( QDataStream & stream, const HbLogContext & context );
            friend QDataStream & operator >>( QDataStream & stream, HbLogContext & context );

        private :

            QString mOwner;
            QString mFile;
            qint32  mLine;
            QString mFunction;

            static QString msApplicationName;
        };
    }
}

using hb::log::HbLogContext;

#endif // HBLOGCONTEXT_H
