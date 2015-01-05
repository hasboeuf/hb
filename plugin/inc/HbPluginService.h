/****************************************************************************
** Copyright (C) 2012-2015 Adrien Gavignet (hasboeuf)
** Contact: adrien.gavignet@gmail.com
**
** This file is part of the Hb module. Provided "AS IS", WITHOUT WARRANTIES
** OR CONDITIONS OF ANY KIND, either express or implied.
****************************************************************************/

#ifndef HBPLUGINSERVICE_H
#define HBPLUGINSERVICE_H

// Qt
#include <QtCore/QObject>
// Local
#include <HbPlugin.h>

namespace hb
{
	namespace plugin
	{
        class HB_PLUGIN_DECL HbPluginService : public QObject
		{
			Q_OBJECT
		public:
            explicit HbPluginService(QString name, QString version, QObject *parent = 0);

			QString name() const;
			QString version() const;

		protected:
			QString mName;
			QString mVersion;

		signals:

			public slots :

		};
	}
}

#endif // HBPLUGINSERVICE_H
