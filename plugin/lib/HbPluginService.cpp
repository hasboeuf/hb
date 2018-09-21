// Local
#include <HbPluginService.h>

using namespace hb::plugin;

HbPluginService::HbPluginService(const QString& name, const QString& version, QObject* parent) : QObject(parent) {
    mName = name;
    mVersion = version;
}

const QString& HbPluginService::name() const {
    return mName;
}

const QString& HbPluginService::version() const {
    return mVersion;
}
