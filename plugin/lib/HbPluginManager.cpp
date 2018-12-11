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
#include <HbPluginInfos.h>
#include <HbPluginManager.h>
#include <IHbPlugin.h>

using namespace hb::plugin;

HbPluginManager::HbPluginManager(HbPluginPlatform* platformService, QObject* parent) : QObject(parent) {
    mpPlatformService = platformService;
}

void HbPluginManager::load(const QString& folder_path) {
    mPath = folder_path;

    scanFolder(mPath);

    auto it_plugin = mPluginsInfos.constBegin();
    while (it_plugin != mPluginsInfos.constEnd()) {
        QString name = it_plugin.key();

        loadPlugin(name);

        ++it_plugin;
    }
}

void HbPluginManager::unload() {
    QStringList names = mPluginsInfos.keys();
    for (QString plugin_name : names) {
        unloadPlugin(plugin_name);
    }

    qDeleteAll(mPluginsInfos); // Delete HbPluginInfos, state will change to PLUGIN_NOT_REGISTERED.

    mPlugins.clear();
    mPluginsInfos.clear();
    mPluginsLoaders.clear();
}

void HbPluginManager::loadPluginFromPath(const QString& plugin_path) {
    HbPluginInfos* infos = scanPlugin(plugin_path);

    if (!infos) {
        return;
    }

    loadPlugin(infos->name());
}

void HbPluginManager::loadPluginFromName(const QString& plugin_name) {
    loadPlugin(plugin_name);
}

void HbPluginManager::unloadPlugin(const QString& plugin_name) {
    HbPluginInfos* infos = mPluginsInfos.value(plugin_name, nullptr);
    Q_ASSERT(infos);

    if (infos->state() < HbPluginInfos::PLUGIN_LOADED_PARTIALLY) {
        return; // Plugin already unloaded.
    }

    infos->setState(HbPluginInfos::PLUGIN_CHANGING); // Transition phase.

    QPluginLoader* loader = mPluginsLoaders.value(plugin_name, nullptr);
    IHbPlugin* plugin = mPlugins.value(plugin_name, nullptr);
    Q_ASSERT(loader);
    Q_ASSERT(plugin);

    for (QString child_name : infos->children()) {
        qWarning() << "Unload child plugin" << child_name;
        if (mPluginsInfos.contains(child_name)) {
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

    infos->setState(HbPluginInfos::PLUGIN_REGISTERED);
}

IHbPlugin* HbPluginManager::plugin(const QString& plugin_name) const {
    if (mPlugins.contains(plugin_name) && mPlugins.value(plugin_name)) {
        return mPlugins.value(plugin_name);
    }

    return nullptr;
}

QList<HbPluginInfos> HbPluginManager::pluginInfoList() {
    QList<HbPluginInfos> plugin_info_list;

    for (const HbPluginInfos* info : mPluginsInfos) {
        Q_ASSERT(info);
        plugin_info_list.append(*info);
    }

    return plugin_info_list;
}

void HbPluginManager::onPluginStateChanged() {
    HbPluginInfos* infos = dynamic_cast<HbPluginInfos*>(sender());
    if (infos) {
        emit pluginStateChanged(*infos);
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
        scanPlugin(file_path); // Add HbPluginInfos.
    }
}

HbPluginInfos* HbPluginManager::scanPlugin(const QString& plugin_path) {
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

    HbPluginInfos* infos = new HbPluginInfos();
    infos->setPath(plugin_path);
    infos->setAuthor(plugin_author);
    infos->setName(plugin_name);
    infos->setVersion(plugin_version);

    if (!plugin_required.isEmpty()) {
        for (QVariant item : plugin_required) {
            QVariantMap map = item.toMap();
            QString name = map.value(QStringLiteral("name")).toString();
            QString version = map.value(QStringLiteral("version")).toString();

            infos->addRequiredPlugin(name, version);
        }
    }

    if (!plugin_optional.isEmpty()) {
        for (QVariant item : plugin_optional) {
            QVariantMap map = item.toMap();
            QString name = map.value(QStringLiteral("name")).toString();
            QString version = map.value(QStringLiteral("version")).toString();

            infos->addOptionalPlugin(name, version);
        }
    }

    if (!service_required.isEmpty()) {
        for (QVariant item : service_required) {
            QVariantMap map = item.toMap();
            QString name = map.value(QStringLiteral("name")).toString();
            QString version = map.value(QStringLiteral("version")).toString();

            infos->addRequiredService(name, version);
        }
    }

    if (!service_optional.isEmpty()) {
        for (QVariant item : service_optional) {
            QVariantMap map = item.toMap();
            QString name = map.value(QStringLiteral("name")).toString();
            QString version = map.value(QStringLiteral("version")).toString();

            infos->addOptionalService(name, version);
        }
    }

    mPluginsInfos.insert(plugin_name, infos);

    connect(infos, &HbPluginInfos::stateChanged, this, &HbPluginManager::onPluginStateChanged);

    infos->setState(HbPluginInfos::PLUGIN_REGISTERED);

    return infos;
}

bool HbPluginManager::loadPlugin(const QString& plugin_name) {
    qDebug() << "Loading plugin" << plugin_name;
    HbPluginInfos* infos = mPluginsInfos.value(plugin_name, nullptr);
    if (!infos) {
        qWarning() << "Plugin absent" << plugin_name;
        return false;
    }

    if (infos->isLoaded()) {
        qDebug() << "Plugin already loaded" << plugin_name;
        return true;
    }

    infos->setState(HbPluginInfos::PLUGIN_CHANGING); // Transition phase.

    QHash<QString, QString> required_plugins = infos->requiredPlugins();
    auto it_rp = required_plugins.constBegin();

    bool required_plugins_ok = true;
    while (it_rp != required_plugins.constEnd()) {
        QString dep_name = it_rp.key();
        QString dep_version = it_rp.value();

        HbPluginInfos* dep = mPluginsInfos.value(dep_name, nullptr);

        if (dep) {
            dep->addChild(plugin_name);

            if (!dep->isLoaded()) {
                qDebug() << "Loading dependency plugin" << dep_name;
                if (!loadPlugin(dep_name)) {
                    qWarning() << "Missing dependency for plugin" << infos->name() << dep_name;
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
            qWarning() << "Missing dependency for plugin" << infos->name() << dep_name;
            required_plugins_ok = false;
        }

        ++it_rp;
    }

    QHash<QString, QString> required_services = infos->requiredServices();
    auto it_rs = required_services.constBegin();

    bool required_services_ok = true;
    while (it_rs != required_services.constEnd()) {
        QString dep_name = it_rs.key();
        QString dep_version = it_rs.value();

        if (!mpPlatformService || mpPlatformService->isServiceRegistered(dep_name) != dep_version) {
            required_services_ok = false;
            qWarning() << "Missing service for plugin" << infos->name() << dep_name;
        }

        ++it_rs;
    }

    if (required_plugins_ok && required_services_ok) {
        QPluginLoader* loader = new QPluginLoader(infos->path());
        if (loader->load()) {
            IHbPlugin* plugin = dynamic_cast<IHbPlugin*>(loader->instance());
            if (plugin) {
                IHbPlugin::PluginInitState state = plugin->init(mpPlatformService);

                if ((state == IHbPlugin::INIT_SUCCESS) || (state == IHbPlugin::INIT_SUCCESS_PARTIALLY)) {
                    mPlugins.insert(infos->name(), plugin);
                    mPluginsLoaders.insert(infos->name(), loader);

                    if (state == IHbPlugin::INIT_SUCCESS) {
                        infos->setState(HbPluginInfos::PLUGIN_LOADED);
                        qDebug() << "Plugin loaded" << infos->name();
                    } else if (state == IHbPlugin::INIT_SUCCESS_PARTIALLY) {
                        infos->setState(HbPluginInfos::PLUGIN_LOADED_PARTIALLY);
                        qDebug() << "Plugin partly loaded" << infos->name();
                    }

                    return true;
                } else // IHbPlugin::INIT_FAIL
                {
                    qWarning() << "Failed to init" << infos->name();
                    delete loader;
                }
            } else {
                qWarning() << "Failed to load" << infos->name() << "does it implement IHbPlugin?";
                delete loader;
            }
        } else {
            qWarning() << "Failed to load" << infos->name() << loader->errorString();
        }
    } else {
        qWarning() << "Plugin not loaded" << infos->name();
    }

    infos->setState(HbPluginInfos::PLUGIN_REGISTERED);
    return false;
}
