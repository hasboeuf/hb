// Qt
#include <QtCore/QDebug>
// Local
#include <HbPluginInfo.h>

using namespace hb::plugin;

HbPluginInfo::HbPluginInfo(QObject* parent) : QObject(parent) {
    mState = PLUGIN_NOT_REGISTERED;
}

HbPluginInfo::~HbPluginInfo() {
    setState(PLUGIN_NOT_REGISTERED);
}

void HbPluginInfo::setPath(const QString& path) {
    mPath = path;
}

void HbPluginInfo::setAuthor(const QString& author) {
    mAuthor = author;
}

void HbPluginInfo::setName(const QString& name) {
    mName = name;
}

void HbPluginInfo::setVersion(const QString& version) {
    mVersion = version;
}

void HbPluginInfo::setState(PluginState state) {
    if (mState != state) {
        mState = state;
        emit stateChanged();
    }
}

bool HbPluginInfo::isLoaded() const {
    if (mState == PLUGIN_LOADED)
        return true;
    if (mState == PLUGIN_LOADED_PARTIALLY)
        return true;

    return false;
}

QString HbPluginInfo::path() const {
    return mPath;
}

QString HbPluginInfo::author() const {
    return mAuthor;
}

QString HbPluginInfo::name() const {
    return mName;
}

QString HbPluginInfo::version() const {
    return mVersion;
}

const QHash<QString, QString>& HbPluginInfo::requiredPlugins() const {
    return mRequiredPlugins;
}

QString HbPluginInfo::requiredPluginsStr() const {
    QString depends;

    auto it = mRequiredPlugins.constBegin();
    while (it != mRequiredPlugins.constEnd()) {
        depends += it.key() + " (" + it.value() + ") ";
        ++it;
    }

    return depends;
}

const QHash<QString, QString>& HbPluginInfo::optionalPlugins() const {
    return mOptionalPlugins;
}

QString HbPluginInfo::optionalPluginsStr() const {
    QString depends;

    auto it = mOptionalPlugins.constBegin();
    while (it != mOptionalPlugins.constEnd()) {
        depends += it.key() + " (" + it.value() + ") ";
        ++it;
    }

    return depends;
}

const QHash<QString, QString>& HbPluginInfo::requiredServices() const {
    return mRequiredService;
}

QString HbPluginInfo::requiredServicesStr() const {
    QString depends;

    auto it = mRequiredService.constBegin();
    while (it != mRequiredService.constEnd()) {
        depends += it.key() + " (" + it.value() + ") ";
        ++it;
    }

    return depends;
}

const QHash<QString, QString>& HbPluginInfo::optionalServices() const {
    return mOptionalService;
}

QString HbPluginInfo::optionalServicesStr() const {
    QString depends;

    auto it = mOptionalService.constBegin();
    while (it != mOptionalService.constEnd()) {
        depends += it.key() + " (" + it.value() + ") ";
        ++it;
    }

    return depends;
}

HbPluginInfo::PluginState HbPluginInfo::state() const {
    return mState;
}

QString HbPluginInfo::stateStr() const {
    return HbPluginInfo::MetaPluginState::toString(mState);
}

const QSet<QString>& HbPluginInfo::children() const {
    return mChildren;
}

bool HbPluginInfo::requiresPlugin(const QString& name) const {
    return mRequiredPlugins.contains(name);
}

void HbPluginInfo::addRequiredPlugin(const QString& name, const QString& version) {
    mRequiredPlugins[name] = version;
}

void HbPluginInfo::addOptionalPlugin(const QString& name, const QString& version) {
    mOptionalPlugins[name] = version;
}

void HbPluginInfo::addRequiredService(const QString& name, const QString& version) {
    mRequiredService[name] = version;
}

void HbPluginInfo::addOptionalService(const QString& name, const QString& version) {
    mOptionalService[name] = version;
}

void HbPluginInfo::addChild(const QString& plugin_name) {
    mChildren.insert(plugin_name);
}
