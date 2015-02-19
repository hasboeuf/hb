// Qt
#include <QtCore/QDir>
#include <QtCore/QDebug>
#include <QtCore/QVariant>
#include <QtCore/QVariantMap>
#include <QtCore/QPluginLoader>
#include <QtCore/QJsonObject>
#include <QtCore/QJsonArray>
// Local
#include <HbPluginManager.h>
#include <HbPluginInterface.h>
#include <HbPluginInfos.h>

using namespace hb::plugin;

HbPluginManager::HbPluginManager(HbPlatformService* platformService, QObject *parent) :
    QObject(parent)
{
    mpPlatformService = platformService;
}

void HbPluginManager::load(QString folder_path)
{
    mPath = folder_path;

    scanFolder(mPath);

    QHash<QString, HbPluginInfos*>::const_iterator it_plugin = mPluginsInfos.constBegin();
    while(it_plugin != mPluginsInfos.constEnd())
    {
        QString name       = it_plugin.key();

        loadPlugin(name);

        ++it_plugin;
    }
}

int HbPluginManager::unload()
{
    foreach(QString plugin_name, mPluginsInfos.keys())
    {
        unloadPlugin(plugin_name, false);
    }

    mPlugins.clear();
    mPluginsInfos.clear();
    mPluginsLoaders.clear();

    return 0;
}

void HbPluginManager::loadPluginFromPath(QString plugin_path)
{
    HbPluginInfos* infos = scanPlugin(plugin_path);

    if(!infos) return;

    loadPlugin(infos->name());
}

void HbPluginManager::loadPluginFromName(QString plugin_name)
{
    loadPlugin(plugin_name);
}

void HbPluginManager::unloadPlugin(QString plugin_name, bool clear)
{
    if(!mLoadedPlugins.contains(plugin_name)) return; // Plugin already unloaded.

    if(!mPluginsLoaders.contains(plugin_name) || !mPluginsLoaders.value(plugin_name)) return;
    if(!mPluginsInfos.contains  (plugin_name) || !mPluginsInfos.value(plugin_name))   return;

    QPluginLoader*   loader = mPluginsLoaders.value(plugin_name);
    HbPluginInfos*     infos  = mPluginsInfos.value(plugin_name);

    foreach(QString child_name, infos->children())
    {
        if(mLoadedPlugins.contains(child_name)) // Plugin already unloaded.
        {
            unloadPlugin(child_name, clear);
        }
    }

    emit pluginUnloaded(infos->name()); // TODO shit !
    qDebug() << QString("Plugin %1 unloaded.").arg(plugin_name);

    loader->unload(); // Delete the plugin.
    delete loader;
    //delete infos; In case of reloading previous loaded plugin.

    loader = 0;
    //infos  = 0; In case of reloading previous loaded plugin.

    if(clear) // = false when called by unload().
    {
        mPlugins.remove       (plugin_name);
        mPluginsLoaders.remove(plugin_name);
        //mPluginsInfos.remove  (plugin_name); In case of reloading previous loaded plugin.
    }

    mLoadedPlugins.remove(plugin_name);
}

HbPluginInterface* HbPluginManager::plugin(QString name) const
{
    if(mPlugins.contains(name) &&
       mPlugins.value(name))
    {
        return mPlugins.value(name);
    }

    return 0;
}

const QList<const HbPluginInfos*> HbPluginManager::pluginInfoList()
{
    QList<const HbPluginInfos*> plugin_info_list;

    foreach(const HbPluginInfos* info, mPluginsInfos)
    {
        if(info)
        {
            plugin_info_list.append(info);
        }
    }

    return plugin_info_list;
}

void HbPluginManager::scanFolder(QString path)
{
    QFileInfo path_info(path);
    if(!path_info.isDir())
    {
        return;
    }

    QDir plugin_dir(path);

    QFileInfoList files = plugin_dir.entryInfoList();

    foreach(QFileInfo file, files)
    {
        if(!file.isFile()) continue;

        QString file_path = file.filePath();

        qDebug() << "->" << file_path;
        scanPlugin(file_path); // Add the HbPluginInfos.
    }
}

HbPluginInfos* HbPluginManager::scanPlugin(QString plugin_path)
{
    if(!QLibrary::isLibrary(plugin_path)) return 0;

    QPluginLoader loader;

    loader.setFileName(plugin_path);

    QString      plugin_name         = loader.metaData().value("MetaData").toObject().value("name").toString();
    QString      plugin_author       = loader.metaData().value("MetaData").toObject().value("author").toString();
    QString      plugin_version      = loader.metaData().value("MetaData").toObject().value("version").toString();
    QVariantList plugin_required     = loader.metaData().value("MetaData").toObject().value("plugin_required").toArray().toVariantList();
    QVariantList plugin_optional     = loader.metaData().value("MetaData").toObject().value("plugin_optional").toArray().toVariantList();
    QVariantList service_required    = loader.metaData().value("MetaData").toObject().value("service_required").toArray().toVariantList();
    QVariantList service_optional    = loader.metaData().value("MetaData").toObject().value("service_optional").toArray().toVariantList();

    HbPluginInfos* info = new HbPluginInfos(plugin_path, plugin_author, plugin_name, plugin_version);

    if(!plugin_required.isEmpty())
    {
        foreach(QVariant item, plugin_required)
        {
            QVariantMap map     = item.toMap();
            QString     name    = map.value("name").toString();
            QString     version = map.value("version").toString();

            info->addRequiredPlugin(name, version);
        }
    }

    if(!plugin_optional.isEmpty())
    {
        foreach(QVariant item, plugin_optional)
        {
            QVariantMap map     = item.toMap();
            QString     name    = map.value("name").toString();
            QString     version = map.value("version").toString();

            info->addOptionalPlugin(name, version);
        }
    }

    if(!service_required.isEmpty())
    {
        foreach(QVariant item, service_required)
        {
            QVariantMap map     = item.toMap();
            QString     name    = map.value("name").toString();
            QString     version = map.value("version").toString();

            info->addRequiredService(name, version);
        }
    }

    if(!service_optional.isEmpty())
    {
        foreach(QVariant item, service_optional)
        {
            QVariantMap map     = item.toMap();
            QString     name    = map.value("name").toString();
            QString     version = map.value("version").toString();

            info->addOptionalService(name, version);
        }
    }

    qDebug() << info->name() << "--" << info->requiredPluginsStr() << "-------" << info->optionalPluginsStr();
    qDebug() << info->name() << "--" << info->requiredServicesStr() << "-------" << info->optionalServicesStr();

    mPluginsInfos.insert(plugin_name, info);

    return info;
}

bool HbPluginManager::loadPlugin(QString name, const HbPluginInfos *child)
{
    if(mLoadedPlugins.contains(name))
    {
        return true;
    }

    if(!mPluginsInfos.contains(name))
    {
        // ERR WTF
        return false;
    }

    HbPluginInfos* infos = mPluginsInfos.value(name);

    QHash<QString, QString> required_plugins       = infos->requiredPlugins();
    QHash<QString, QString>::const_iterator it_rp  = required_plugins.constBegin();

    bool required_plugins_ok = true;
    while(it_rp != required_plugins.constEnd())
    {

        QString dep_name    = it_rp.key();
        QString dep_version = it_rp.value();

        if(!mLoadedPlugins.contains(dep_name))
        {
            if(!loadPlugin(dep_name, infos))
            {
                qDebug() << QString("Missing dependency for plugin %1: %2.").arg(infos->name()).arg(dep_name);
                required_plugins_ok = false;
            }
        }

        if(mLoadedPlugins.value(dep_name) != dep_version)
        {
            qDebug() << QString("Version mismatch for plugin %1: current=%2, required=%3.")
                        .arg(dep_name)
                        .arg(mLoadedPlugins.value(dep_name))
                        .arg(dep_version);

            required_plugins_ok = false;
        }

        it_rp++;
    }

    QHash<QString, QString> required_services      = infos->requiredServices();
    QHash<QString, QString>::const_iterator it_rs  = required_services.constBegin();

    bool required_services_ok = true;
    while(it_rs != required_services.constEnd())
    {

        QString dep_name    = it_rs.key();
        QString dep_version = it_rs.value();

        if(!mpPlatformService || mpPlatformService->isServiceRegistered(dep_name) != dep_version)
        {
            required_services_ok = false;
            qDebug() << QString("Missing service for plugin %1: %2.").arg(infos->name()).arg(dep_name);
        }

        it_rs++;
    }

    if(!required_plugins_ok || !required_services_ok)
    {
        qDebug() << QString("Plugin %1 not loaded.").arg(infos->name());

        return false;
    }


    QPluginLoader *loader = new QPluginLoader(infos->path());
    loader->load();
    if(!loader->isLoaded())
    {
        return false;
    }

    HbPluginInterface* plugin = dynamic_cast<HbPluginInterface*>(loader->instance());
    if(plugin)
    {
        if(child)
        {
            infos->addChild(child->name());
        }

        if(plugin->init(mpPlatformService) == HbPluginInterface::INIT_FAIL)
        {
            delete loader;
            return false;
        }

        mPlugins.insert       (infos->name(), plugin);
        mPluginsLoaders.insert(infos->name(), loader);

        mLoadedPlugins.insert(infos->name(), infos->version());

        qDebug() << QString("Plugin %1 loaded.").arg(infos->name());

        emit pluginLoaded(infos);
        return true;
    }
    else
    {
        delete loader;
        return false;
    }
}
