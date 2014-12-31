/****************************************************************************
** Copyright (C) 2012-2015 Adrien Gavignet (hasboeuf)
** Contact: adrien.gavignet@gmail.com
**
** This file is part of the Hb module. Provided "AS IS", WITHOUT WARRANTIES
** OR CONDITIONS OF ANY KIND, either express or implied.
****************************************************************************/

#ifndef HBPLUGINMANAGER_H
#define HBPLUGINMANAGER_H

// Qt
#include <QtCore/QObject>
#include <QtCore/QHash>
// Local
#include <HbPluginInfos.h>

class QPluginLoader;

namespace hb
{
	namespace plugin
	{
		class HbPluginInterface;
		class HbPlatformService;

        class HbPluginManager : public QObject
		{
			Q_OBJECT
		public:
            explicit HbPluginManager(HbPlatformService* platformService, QObject *parent = 0);

			void load(QString folder_path);
			int  unload();

			void loadPluginFromPath(QString plugin_path);
			void loadPluginFromName(QString plugin_name);
			void unloadPlugin(QString plugin_name, bool clear = true);

			QHash<QString, QString> mLoadedPlugins; // Name Version.

			HbPluginInterface* plugin(QString name) const;

			const QList<const HbPluginInfos*> pluginInfoList();

		private:
			void         scanFolder(QString folder_path);
			HbPluginInfos* scanPlugin(QString plugin_path);
			bool         loadPlugin(QString name, const HbPluginInfos* child = 0);

		signals:
			void pluginLoaded(const HbPluginInfos* plugin_infos);
			void pluginLoadingFailed(const HbPluginInfos* plugin_infos);
			void pluginUnloaded(QString            plugin_name);

			public slots:


		private:
			HbPlatformService* mpPlatformService;

			QString mPath;

			QHash<QString, HbPluginInfos*>     mPluginsInfos;
			QHash<QString, QPluginLoader*>   mPluginsLoaders;
			QHash<QString, HbPluginInterface*> mPlugins;

		};
	}
}

#endif // HBPLUGINMANAGER_H
