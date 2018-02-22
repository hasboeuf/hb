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

// Qt
#include <QtCore/QDataStream>
#include <QtCore/QDebug>
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
        public:

            HbLogContext();
            virtual ~HbLogContext() = default;
            HbLogContext( const QMessageLogContext & context );

            HbLogContext( const HbLogContext & context );
            HbLogContext & operator =( const HbLogContext & context );

            const QString & owner   () const;
            qint32          thread  () const;
            const QString & file    () const;
            qint32          line    () const;
            const QString & function() const;

            void setOwner   ( const QString & owner );
            void setThread  ( qint32 thread );
            void setFile    ( const QString & file );
            void setLine    ( quint32 line );
            void setFunction( const QString & function );

            void print ( QtMsgType type, const QString & message ) const;

            friend QDataStream & operator <<( QDataStream & stream, const HbLogContext & context );
            friend QDataStream & operator >>( QDataStream & stream, HbLogContext & context );

        private:

            QString mOwner;
            qint32 mThread;
            QString mFile;
            quint32  mLine;
            QString mFunction;

            static QString msApplicationName;
        };
    }
}

using hb::log::HbLogContext;

#endif // HBLOGCONTEXT_H
