/****************************************************************************
** Copyright (C) 2012-2015 Adrien Gavignet (hasboeuf)
** Contact: adrien.gavignet@gmail.com
**
** This file is part of the Hb module. Provided "AS IS", WITHOUT WARRANTIES
** OR CONDITIONS OF ANY KIND, either express or implied.
****************************************************************************/

#ifndef HBSTEADYTIME_H
#define HBSTEADYTIME_H

// System
#include <chrono>
// Qt
#include <QtCore/QDateTime>
// Local
#include <HbTools.h>

using namespace std::chrono;

namespace hb
{
	namespace tools
	{
        class HB_TOOLS_DECL HbSteadyTime
		{

		public:
            static HbSteadyTime now();
            static HbSteadyTime fromDateTime( const QDateTime & datatime, quint64 steady = 0 );
            static HbSteadyTime fromString( const QString & format, const QString & value );
            QString toString( const QString & format );

            const QDateTime & datetime() const;
            quint64 steady() const;

        protected:
            HbSteadyTime();

        private:
            QDateTime mDateTime;
            quint64   mSteady;
		};
	}
}

#endif // HBSTEADYTIME_H
