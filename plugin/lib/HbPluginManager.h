/****************************************************************************
** Copyright (C) 2012-2015 Adrien Gavignet (hasboeuf)
** Contact: adrien.gavignet@gmail.com
**
** This file is part of the Hb module. Provided "AS IS", WITHOUT WARRANTIES
** OR CONDITIONS OF ANY KIND, either express or implied.
****************************************************************************/

#ifndef HBPLUGINMANAGER_H
#define HBPLUGINMANAGER_H

/*! \file HbPluginManager.h */

// Qt
#include <QtCore/QHash>
#include <QtCore/QObject>
// Local
#include <HbPlugin.h>
#include <HbPluginInfo.h>

class QPluginLoader;

namespace hb {
namespace plugin {
class IHbPlugin;
class HbPluginPlatform;

/*!
 * HbPluginManager handles plugins.
 * Scan folders, seek for libraries, load plugins.
 */
class HB_PLUGIN_DECL HbPluginManager : public QObject {
    Q_OBJECT
public:
    explicit HbPluginManager(HbPluginPlatform* platformService, QObject* parent = nullptr);

    /*!
     * Load plugin contained in folder path.
     * \param folder_path Folder path.
     */
    void load(const QString& folder_path);

    /*!
     * Unload all plugins previously loaded.
     */
    void unload();

    /*!
     * Load a specific plugin.
     * \param plugin_path Path to the library to load.
     */
    void loadPluginFromPath(const QString& plugin_path);

    /*!
     * Load a specific plugin.
     * \param plugin_name Plugin name.
     */
    void loadPluginFromName(const QString& plugin_name);
    /*!
     * Unload a specific plugin.
     * \param plugin_name Plugin name.
     */
    void unloadPlugin(const QString& plugin_name);

    /*!
     * Get a specific plugin.
     * \param plugin_name Plugin name.
     */
    IHbPlugin* plugin(const QString& plugin_name) const;

    /*!
     * Return previously scanned plugins info.
     * \return Plugin info list.
     */
    QList<HbPluginInfo*> pluginInfoList();

    void onPluginStateChanged();

signals:
    /*!
     * Triggered when the state has changed.
     * To HbPluginManager.
     */
    void pluginStateChanged(const HbPluginInfo& plugin_info);

private:
    void scanFolder(const QString& folder_path);
    HbPluginInfo* scanPlugin(const QString& plugin_path);
    bool loadPlugin(const QString& plugin_name);

    HbPluginPlatform* mPlatformService;

    QString mPath;

    QHash<QString, HbPluginInfo*> mPluginsInfo;
    QHash<QString, QPluginLoader*> mPluginsLoaders;
    QHash<QString, IHbPlugin*> mPlugins;
};
} // namespace plugin
} // namespace hb

#endif // HBPLUGINMANAGER_H
