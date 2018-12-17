// Qt
#include <QtCore/QDebug>
#include <QtCore/QDir>
#include <QtCore/QJsonArray>
#include <QtCore/QJsonObject>
#include <QtCore/QPluginLoader>
#include <QtCore/QVariant>
#include <QtCore/QVariantMap>
// Hb
#include <HbGlobal.h>
#include <HbLogService.h>
// Local
#include <HbPluginInfo.h>
#include <HbPluginManager.h>
#include <IHbPlugin.h>

using namespace hb::plugin;

HbPluginManager::HbPluginManager(HbPluginPlatform* platformService, QObject* parent) : QObject(parent) {
    mPlatformService = platformService;
}

void HbPluginManager::load(const QString& folder_path) {
    mPath = folder_path;

    scanFolder(mPath);

    auto it_plugin = mPluginsInfo.constBegin();
    while (it_plugin != mPluginsInfo.constEnd()) {
        QString name = it_plugin.key();

        loadPlugin(name);

        ++it_plugin;
    }
}

void HbPluginManager::unload() {
    QStringList names = mPluginsInfo.keys();
    for (QString plugin_name : names) {
        unloadPlugin(plugin_name);
    }

    qDeleteAll(mPluginsInfo); // Delete HbPluginInfo, state will change to PLUGIN_NOT_REGISTERED.

    mPlugins.clear();
    mPluginsInfo.clear();
    mPluginsLoaders.clear();
}

void HbPluginManager::loadPluginFromPath(const QString& plugin_path) {
    HbPluginInfo* info = scanPlugin(plugin_path);

    if (!info) {
        return;
    }

    loadPlugin(info->name());
}

void HbPluginManager::loadPluginFromName(const QString& plugin_name) {
    loadPlugin(plugin_name);
}

void HbPluginManager::unloadPlugin(const QString& plugin_name) {
    HbPluginInfo* info = mPluginsInfo.value(plugin_name, nullptr);
    Q_ASSERT(info);

    if (info->state() < HbPluginInfo::PLUGIN_LOADED_PARTIALLY) {
        return; // Plugin already unloaded.
    }

    info->setState(HbPluginInfo::PLUGIN_CHANGING); // Transition phase.

    QPluginLoader* loader = mPluginsLoaders.value(plugin_name, nullptr);
    IHbPlugin* plugin = mPlugins.value(plugin_name, nullptr);
    Q_ASSERT(loader);
    Q_ASSERT(plugin);

    for (QString child_name : info->children()) {
        qWarning() << "Unload child plugin" << child_name;
        if (mPluginsInfo.contains(child_name)) {
            unloadPlugin(child_name);
        }
    }

    qDebug() << "Plugin unloaded" << plugin_name;

    plugin->unload();

    mPlugins.remove(plugin_name);
    mPluginsLoaders.remove(plugin_name);

    loader->unload(); // Delete the plugin.
    delete loader;
    loader = 0;

    info->setState(HbPluginInfo::PLUGIN_REGISTERED);
}

IHbPlugin* HbPluginManager::plugin(const QString& plugin_name) const {
    if (mPlugins.contains(plugin_name) && mPlugins.value(plugin_name)) {
        return mPlugins.value(plugin_name);
    }

    return nullptr;
}

QList<HbPluginInfo*> HbPluginManager::pluginInfoList() {
    return mPluginsInfo.values();
}

void HbPluginManager::onPluginStateChanged() {
    HbPluginInfo* info = dynamic_cast<HbPluginInfo*>(sender());
    if (info) {
        emit pluginStateChanged(*info);
    }
}

void HbPluginManager::scanFolder(const QString& path) {
    QFileInfo path_info(path);
    if (!path_info.isDir()) {
        return;
    }

    QDir plugin_dir(path);

    qDebug() << "Scan directory" << path;

    QFileInfoList files = plugin_dir.entryInfoList();

    for (QFileInfo file : files) {
        if (!file.isFile())
            continue;

        QString file_path = file.filePath();

        qDebug() << "Scan file" << file_path;
        scanPlugin(file_path); // Add HbPluginInfo.
    }
}

HbPluginInfo* HbPluginManager::scanPlugin(const QString& plugin_path) {
    if (!QLibrary::isLibrary(plugin_path))
        return nullptr;

    QPluginLoader loader;

    loader.setFileName(plugin_path);

    QString plugin_name = loader.metaData().value("MetaData").toObject().value("name").toString();
    QString plugin_author = loader.metaData().value("MetaData").toObject().value("author").toString();
    QString plugin_version = loader.metaData().value("MetaData").toObject().value("version").toString();
    QVariantList plugin_required =
        loader.metaData().value("MetaData").toObject().value("plugin_required").toArray().toVariantList();
    QVariantList plugin_optional =
        loader.metaData().value("MetaData").toObject().value("plugin_optional").toArray().toVariantList();
    QVariantList service_required =
        loader.metaData().value("MetaData").toObject().value("service_required").toArray().toVariantList();
    QVariantList service_optional =
        loader.metaData().value("MetaData").toObject().value("service_optional").toArray().toVariantList();

    HbPluginInfo* info = new HbPluginInfo();
    info->setPath(plugin_path);
    info->setAuthor(plugin_author);
    info->setName(plugin_name);
    info->setVersion(plugin_version);

    if (!plugin_required.isEmpty()) {
        for (QVariant item : plugin_required) {
            QVariantMap map = item.toMap();
            QString name = map.value(QStringLiteral("name")).toString();
            QString version = map.value(QStringLiteral("version")).toString();

            info->addRequiredPlugin(name, version);
        }
    }

    if (!plugin_optional.isEmpty()) {
        for (QVariant item : plugin_optional) {
            QVariantMap map = item.toMap();
            QString name = map.value(QStringLiteral("name")).toString();
            QString version = map.value(QStringLiteral("version")).toString();

            info->addOptionalPlugin(name, version);
        }
    }

    if (!service_required.isEmpty()) {
        for (QVariant item : service_required) {
            QVariantMap map = item.toMap();
            QString name = map.value(QStringLiteral("name")).toString();
            QString version = map.value(QStringLiteral("version")).toString();

            info->addRequiredService(name, version);
        }
    }

    if (!service_optional.isEmpty()) {
        for (QVariant item : service_optional) {
            QVariantMap map = item.toMap();
            QString name = map.value(QStringLiteral("name")).toString();
            QString version = map.value(QStringLiteral("version")).toString();

            info->addOptionalService(name, version);
        }
    }

    mPluginsInfo.insert(plugin_name, info);

    connect(info, &HbPluginInfo::stateChanged, this, &HbPluginManager::onPluginStateChanged);

    info->setState(HbPluginInfo::PLUGIN_REGISTERED);

    return info;
}

bool HbPluginManager::loadPlugin(const QString& plugin_name) {
    qDebug() << "Loading plugin" << plugin_name;
    HbPluginInfo* info = mPluginsInfo.value(plugin_name, nullptr);
    if (!info) {
        qWarning() << "Plugin absent" << plugin_name;
        return false;
    }

    if (info->isLoaded()) {
        qDebug() << "Plugin already loaded" << plugin_name;
        return true;
    }

    info->setState(HbPluginInfo::PLUGIN_CHANGING); // Transition phase.

    QHash<QString, QString> required_plugins = info->requiredPlugins();
    auto it_rp = required_plugins.constBegin();

    bool required_plugins_ok = true;
    while (it_rp != required_plugins.constEnd()) {
        QString dep_name = it_rp.key();
        QString dep_version = it_rp.value();

        HbPluginInfo* dep = mPluginsInfo.value(dep_name, nullptr);

        if (dep) {
            dep->addChild(plugin_name);

            if (!dep->isLoaded()) {
                qDebug() << "Loading dependency plugin" << dep_name;
                if (!loadPlugin(dep_name)) {
                    qWarning() << "Missing dependency for plugin" << info->name() << dep_name;
                    required_plugins_ok = false;
                }
            }

            if (dep->isLoaded()) {
                if (dep->version() != dep_version) {
                    qDebug() << QString("Version mismatch for plugin %1: current=%2, required=%3.")
                                    .arg(dep_name)
                                    .arg(dep->version())
                                    .arg(dep_version);

                    required_plugins_ok = false;
                }
            }
        } else {
            qWarning() << "Missing dependency for plugin" << info->name() << dep_name;
            required_plugins_ok = false;
        }

        ++it_rp;
    }

    QHash<QString, QString> required_services = info->requiredServices();
    auto it_rs = required_services.constBegin();

    bool required_services_ok = true;
    while (it_rs != required_services.constEnd()) {
        QString dep_name = it_rs.key();
        QString dep_version = it_rs.value();

        if (!mPlatformService || mPlatformService->isServiceRegistered(dep_name) != dep_version) {
            required_services_ok = false;
            qWarning() << "Missing service for plugin" << info->name() << dep_name;
        }

        ++it_rs;
    }

    if (required_plugins_ok && required_services_ok) {
        QPluginLoader* loader = new QPluginLoader(info->path());
        if (loader->load()) {
            IHbPlugin* plugin = dynamic_cast<IHbPlugin*>(loader->instance());
            if (plugin) {
                IHbPlugin::PluginInitState state = plugin->init(mPlatformService);

                if ((state == IHbPlugin::INIT_SUCCESS) || (state == IHbPlugin::INIT_SUCCESS_PARTIALLY)) {
                    mPlugins.insert(info->name(), plugin);
                    mPluginsLoaders.insert(info->name(), loader);

                    if (state == IHbPlugin::INIT_SUCCESS) {
                        info->setState(HbPluginInfo::PLUGIN_LOADED);
                        qDebug() << "Plugin loaded" << info->name();
                    } else if (state == IHbPlugin::INIT_SUCCESS_PARTIALLY) {
                        info->setState(HbPluginInfo::PLUGIN_LOADED_PARTIALLY);
                        qDebug() << "Plugin partly loaded" << info->name();
                    }

                    return true;
                } else // IHbPlugin::INIT_FAIL
                {
                    qWarning() << "Failed to init" << info->name();
                    delete loader;
                }
            } else {
                qWarning() << "Failed to load" << info->name() << "does it implement IHbPlugin?";
                delete loader;
            }
        } else {
            qWarning() << "Failed to load" << info->name() << loader->errorString();
        }
    } else {
        qWarning() << "Plugin not loaded" << info->name();
    }

    info->setState(HbPluginInfo::PLUGIN_REGISTERED);
    return false;
}
