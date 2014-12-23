// Local
#include <HbPluginService.h>

using namespace hb::plugin;

HbPluginService::HbPluginService(QString name, QString version, QObject *parent) :
    QObject(parent)
{
    mName    = name;
    mVersion = version;
}

QString HbPluginService::name() const
{
    return mName;
}

QString HbPluginService::version() const
{
    return mVersion;
}
