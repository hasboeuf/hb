/****************************************************************************
** Copyright (C) 2012-2015 Adrien Gavignet (hasboeuf)
** Contact: adrien.gavignet@gmail.com
**
** This file is part of the Hb module. Provided "AS IS", WITHOUT WARRANTIES
** OR CONDITIONS OF ANY KIND, either express or implied.
****************************************************************************/

#ifndef HBLOGMESSAGE_H
#define HBLOGMESSAGE_H

/*! \file HbLogMessage.h */

// Hb
#include <HbLogContext.h>

namespace hb
{	
	namespace log
	{


		/*! \namespace hb::log */

        /*! 
        * \class HbLogMessage
        * \brief The %HbLogMessage class defines a logger message.
        *
        * %HbLogMessage TODO DOC.\n
        */
        class HB_LOG_DECL HbLogMessage final : public QObject
		{
		public:

            static const QString msFieldSeparator;
            static const HbLogMessage * fromRaw( const QString & raw); // Use for export.
            static const QString toRaw( const HbLogMessage & msg );                              // Use for import.

            HbLogMessage();
            HbLogMessage( HbLogger::Level level, HbLogger::Formats format,
                            const HbLogContext & context, qint32 timeTag, const QString & message );
            HbLogMessage( const HbLogMessage & message );
            virtual ~HbLogMessage() = default;
				
            HbLogMessage & operator =( const HbLogMessage & message );

            bool system() const;
            HbLogger::Level level() const;
            QString levelStr( bool spacing = true ) const;
            const HbLogContext & context() const;

            qint32 timeTag() const;
            QString timeTagStr() const;
            const QString & message() const;

            QString toString() const;

            QByteArray toByteArray() const;
			void fromDataStream( QDataStream & stream );


		private :

            HbLogger::Level mLevel;
            HbLogger::Formats mFormat;
            HbLogContext mContext;

            qint32 mTimeTag;
			QString mMessage;
		};
	}
}

Q_DECLARE_METATYPE( hb::log::HbLogMessage )

#endif // HBLOGMESSAGE_H
