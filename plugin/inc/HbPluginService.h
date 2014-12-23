#ifndef HBPLUGINSERVICE_H
#define HBPLUGINSERVICE_H

// Copyright (C) 2012-2014
// Adrien Gavignet (hasboeuf)
// adrien.gavignet@gmail.com

// Qt
#include <QtCore/QObject>

namespace hb
{
	namespace plugin
	{
        class HbPluginService : public QObject
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
