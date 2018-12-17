/****************************************************************************
** Copyright (C) 2012-2015 Adrien Gavignet (hasboeuf)
** Contact: adrien.gavignet@gmail.com
**
** This file is part of the Hb module. Provided "AS IS", WITHOUT WARRANTIES
** OR CONDITIONS OF ANY KIND, either express or implied.
****************************************************************************/

#ifndef HBPLUGINPLATFORM_H
#define HBPLUGINPLATFORM_H

/*! \file HbPluginPlatform.h */

// Qt
#include <QtCore/QHash>
#include <QtCore/QObject>
// Local
#include <HbPlugin.h>
#include <HbPluginInfos.h>
#include <HbPluginManager.h>

namespace hb {
namespace plugin {
class IHbPlugin;
class HbPluginService;

/*!
 * HbPluginPlatform manages services and handles plugin manager.
 */
class HB_PLUGIN_DECL HbPluginPlatform : public QObject {
    Q_OBJECT

public:
    explicit HbPluginPlatform(QObject* parent = nullptr);

    /*!
     * Load plugins contained in a folder.
     * The folder is scanned and all library files are loaded.
     * \param plugin_folder Folder to scan.
     */
    void loadPlugins(const QString& plugin_folder);

    /*!
     * Unload all currently loaded plugins.
     */
    void unloadPlugins();

    /*!
     * Return previously scanned plugins infos.
     * \return Plugin infos list.
     */
    QList<HbPluginInfos*> pluginInfoList();

    /*!
     * Get a service.
     * \param name Service name.
     * \return Requested service or nullptr if not found.
     */
    virtual HbPluginService* requestService(const QString& name) const;

    /*!
     * Get a plugin.
     * \param name Plugin name.
     * \return Requested plugin or nullptr if not found.
     */
    virtual const IHbPlugin* requestPlugin(const QString& name) const;

    /*!
     * Register a service.
     * \param service Service to register.
     */
    virtual void registerService(HbPluginService* service);

    /*!
     * Check if a service is registered.
     * \param service_name Service name.
     * \return Version of the service or "" if not registered.
     */
    virtual QString isServiceRegistered(const QString& service_name) const;

    /*!
     * Fired when a plugin has changed its state.
     * From HbPluginManager.
     */
    void onPluginStateChanged(const HbPluginInfos& plugin_infos);

    /*!
     * Fired when user requests to load a plugin.
     * From GUI.
     * \param plugin_name Plugin name.
     */
    void onLoadPluginRequest(const QString& plugin_name);

    /*!
     * Fired when user requests to unload a plugin.
     * From GUI.
     * \param plugin_name Plugin name.
     */
    void onUnloadPluginRequest(const QString& plugin_name);

signals:
    /*!
     * Triggered when a plugin has changed its state.
     * To GUI.
     */
    void pluginStateChanged(const HbPluginInfos& plugin_infos);

protected:
    bool mPluginLoaded;
    HbPluginManager mPluginManager;
    QHash<QString, HbPluginService*> mServices;
};
} // namespace plugin
} // namespace hb

#endif // HBPLUGINPLATFORM_H
