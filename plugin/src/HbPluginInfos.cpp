// Local
#include <HbPluginInfos.h>

using namespace hb::plugin;

HbPluginInfos::HbPluginInfos(QString path, QString author, QString name, QString version)
{
    mPath    = path;
    mAuthor  = author;
    mName    = name;
    mVersion = version;
    mState   = PLUGIN_NOT_LOADED;
}

HbPluginInfos::HbPluginInfos(const HbPluginInfos& copy)
{
    mPath    = copy.mPath;
    mAuthor  = copy.mAuthor;
    mName    = copy.mName;
    mVersion = copy.mVersion;
    mState   = copy.mState;

    mRequiredPlugins = copy.mRequiredPlugins;
    mOptionalPlugins = copy.mOptionalPlugins;
    mRequiredService = copy.mRequiredService;
    mOptionalService = copy.mOptionalService;

    mChildren = copy.mChildren;
}

HbPluginInfos& HbPluginInfos::operator=(const HbPluginInfos& copy)
{
    mPath    = copy.mPath;
    mAuthor  = copy.mAuthor;
    mName    = copy.mName;
    mVersion = copy.mVersion;
    mState   = copy.mState;

    mRequiredPlugins = copy.mRequiredPlugins;
    mOptionalPlugins = copy.mOptionalPlugins;
    mRequiredService = copy.mRequiredService;
    mOptionalService = copy.mOptionalService;

    mChildren = copy.mChildren;

    return (*this);
}

QString HbPluginInfos::path() const
{
    return mPath;
}

QString HbPluginInfos::author() const
{
    return mAuthor;
}

QString HbPluginInfos::name() const
{
    return mName;
}

QString HbPluginInfos::version() const
{
    return mVersion;
}

QHash<QString, QString> HbPluginInfos::requiredPlugins() const
{
    return mRequiredPlugins;
}

QString HbPluginInfos::requiredPluginsStr() const
{
    QString depends;

    QHash<QString, QString>::const_iterator it = mRequiredPlugins.constBegin();
    while(it != mRequiredPlugins.constEnd())
    {
        depends += it.key() + " (" + it.value() + ") ";
        ++it;
    }

    return depends;

}

QHash<QString, QString> HbPluginInfos::optionalPlugins() const
{
    return mOptionalPlugins;
}

QString HbPluginInfos::optionalPluginsStr() const
{
    QString depends;

    QHash<QString, QString>::const_iterator it = mOptionalPlugins.constBegin();
    while(it != mOptionalPlugins.constEnd())
    {
        depends += it.key() + " (" + it.value() + ") ";
        ++it;
    }

    return depends;

}

QHash<QString, QString> HbPluginInfos::requiredServices() const
{
    return mRequiredService;
}

QString HbPluginInfos::requiredServicesStr() const
{
    QString depends;

    QHash<QString, QString>::const_iterator it = mRequiredService.constBegin();
    while(it != mRequiredService.constEnd())
    {
        depends += it.key() + " (" + it.value() + ") ";
        ++it;
    }

    return depends;

}

QHash<QString, QString> HbPluginInfos::optionalServices() const
{
    return mOptionalService;
}

QString HbPluginInfos::optionalServicesStr() const
{
    QString depends;

    QHash<QString, QString>::const_iterator it = mOptionalService.constBegin();
    while(it != mOptionalService.constEnd())
    {
        depends += it.key() + " (" + it.value() + ") ";
        ++it;
    }

    return depends;

}

HbPluginInfos::PluginState HbPluginInfos::state() const
{
    return mState;
}

QString HbPluginInfos::stateStr() const
{
    if(mState == PLUGIN_NOT_LOADED)       return "Plugin not loaded.";
    if(mState == PLUGIN_NOT_LOADED_ERROR) return "Plugin not loaded (errors occured).";
    if(mState == PLUGIN_LOADED)           return "Plugin loaded.";
    else                                  return "Plugin state unknown.";
}

const QStringList& HbPluginInfos::children() const
{
    return mChildren;
}

bool HbPluginInfos::requiresPlugin(QString name) const
{
    return mRequiredPlugins.contains(name);
}

void HbPluginInfos::addRequiredPlugin(QString name, QString version)
{
    mRequiredPlugins[name] = version;
}

void HbPluginInfos::addOptionalPlugin(QString name, QString version)
{
    mOptionalPlugins[name] = version;
}

void HbPluginInfos::addRequiredService(QString name, QString version)
{
    mRequiredService[name] = version;
}

void HbPluginInfos::addOptionalService(QString name, QString version)
{
    mOptionalService[name] = version;
}

void HbPluginInfos::addChild(QString plugin_name)
{
    mChildren.append(plugin_name);
}
