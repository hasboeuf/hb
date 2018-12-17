// Qt
#include <QtCore/QDebug>
// Hb
#include <HbLogService.h>
// Local
#include <HbPluginInfo.h>
#include <HbPluginPlatform.h>
#include <HbPluginService.h>
#include <IHbPlugin.h>

using namespace hb::plugin;

HbPluginPlatform::HbPluginPlatform(QObject* parent) : QObject(parent), mPluginManager(this) {
    connect(&mPluginManager,
            &HbPluginManager::pluginStateChanged,
            this,
            &HbPluginPlatform::onPluginStateChanged,
            Qt::UniqueConnection);
}

void HbPluginPlatform::loadPlugins(const QString& plugin_folder) {
    mPluginManager.load(plugin_folder);
}

void HbPluginPlatform::unloadPlugins() {
    mPluginManager.unload();
}

QList<HbPluginInfo*> HbPluginPlatform::pluginInfoList() {
    return mPluginManager.pluginInfoList();
}

HbPluginService* HbPluginPlatform::requestService(const QString& service_name) const {
    if (mServices.contains(service_name) && mServices.value(service_name)) {
        return mServices.value(service_name);
    }

    return nullptr;
}

void HbPluginPlatform::registerService(HbPluginService* service) {
    if (!service) {
        return;
    }

    QString name = service->name();

    if (mServices.contains(name)) {
        return;
    }

    mServices.insert(name, service);
}

const IHbPlugin* HbPluginPlatform::requestPlugin(const QString& name) const {
    return mPluginManager.plugin(name);
}

QString HbPluginPlatform::isServiceRegistered(const QString& service_name) const {
    if (mServices.contains(service_name) && mServices.value(service_name)) {
        return mServices.value(service_name)->version();
    }

    return QString();
}

void HbPluginPlatform::onPluginStateChanged(const HbPluginInfo& plugin_info) {
    emit pluginStateChanged(plugin_info);
}

void HbPluginPlatform::onLoadPluginRequest(const QString& plugin_name) {
    qDebug() << "Load request plugin" << plugin_name;
    mPluginManager.loadPluginFromName(plugin_name);
}

void HbPluginPlatform::onUnloadPluginRequest(const QString& plugin_name) {
    qDebug() << "Unload request plugin" << plugin_name;
    mPluginManager.unloadPlugin(plugin_name);
}
