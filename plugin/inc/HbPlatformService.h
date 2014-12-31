/****************************************************************************
** Copyright (C) 2012-2015 Adrien Gavignet (hasboeuf)
** Contact: adrien.gavignet@gmail.com
**
** This file is part of the Hb module. Provided "AS IS", WITHOUT WARRANTIES
** OR CONDITIONS OF ANY KIND, either express or implied.
****************************************************************************/

#ifndef HBPLATFORMSERVICE_H
#define HBPLATFORMSERVICE_H

// Qt
#include <QtCore/QObject>
#include <QtCore/QHash>
// Local
#include <HbPluginManager.h>
#include <HbPluginInfos.h>


namespace hb
{
	namespace plugin
	{
		class HbPluginInterface;
		class HbPluginService;

        class HbPlatformService : public QObject
		{
			Q_OBJECT

		public:

            explicit HbPlatformService();
            virtual ~HbPlatformService();

			void loadPlugins(QString plugin_folder);
			void unloadPlugins();

			const QList<const HbPluginInfos *> pluginInfoList();

			virtual HbPluginService*               requestService(QString name) const;
			virtual const HbPluginInterface* requestPlugin(QString name) const;

			virtual void                   registerService(HbPluginService* service);

			virtual QString                isServiceRegistered(QString service_name) const;

		protected:
			bool                             mPluginLoaded;
            HbPluginManager                    mPluginManager;
			QHash<QString, HbPluginService*>         mServices;

		signals:
			// To GUI
			void pluginLoaded(const HbPluginInfos* plugin_infos);
			void pluginUnloaded(QString            plugin_name);

			public slots:
			// From HbPluginManager
			void onPluginLoaded(const HbPluginInfos* plugin_infos);
			void onPluginUnloaded(QString plugin_name);

			// From GUI
			void onLoadPluginRequest(QString plugin_name);
			void onUnloadPluginRequest(QString plugin_name);
		};
	}
}

#endif // HBPLATFORMSERVICE_H
