// Local
#include <HbPluginInfos.h>

using namespace hb::plugin;

HbPluginInfos::HbPluginInfos( const QString & path, const QString & author, const QString & name, const QString & version )
{
    mPath    = path;
    mAuthor  = author;
    mName    = name;
    mVersion = version;
    mState   = PLUGIN_NOT_LOADED;
}

HbPluginInfos::HbPluginInfos( const HbPluginInfos & copy )
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

HbPluginInfos& HbPluginInfos::operator=( const HbPluginInfos & copy )
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

    return ( *this );
}

const QString & HbPluginInfos::path() const
{
    return mPath;
}

const QString & HbPluginInfos::author() const
{
    return mAuthor;
}

const QString & HbPluginInfos::name() const
{
    return mName;
}

const QString & HbPluginInfos::version() const
{
    return mVersion;
}

const QHash< QString, QString > & HbPluginInfos::requiredPlugins() const
{
    return mRequiredPlugins;
}

QString HbPluginInfos::requiredPluginsStr() const
{
    QString depends;

    auto it = mRequiredPlugins.constBegin();
    while(it != mRequiredPlugins.constEnd())
    {
        depends += it.key() + " (" + it.value() + ") ";
        ++it;
    }

    return depends;

}

const QHash<QString, QString> & HbPluginInfos::optionalPlugins() const
{
    return mOptionalPlugins;
}

QString HbPluginInfos::optionalPluginsStr() const
{
    QString depends;

    auto it = mOptionalPlugins.constBegin();
    while( it != mOptionalPlugins.constEnd() )
    {
        depends += it.key() + " (" + it.value() + ") ";
        ++it;
    }

    return depends;

}

const QHash< QString, QString > & HbPluginInfos::requiredServices() const
{
    return mRequiredService;
}

QString HbPluginInfos::requiredServicesStr() const
{
    QString depends;

    auto it = mRequiredService.constBegin();
    while( it != mRequiredService.constEnd() )
    {
        depends += it.key() + " (" + it.value() + ") ";
        ++it;
    }

    return depends;

}

const QHash< QString, QString > & HbPluginInfos::optionalServices() const
{
    return mOptionalService;
}

QString HbPluginInfos::optionalServicesStr() const
{
    QString depends;

    auto it = mOptionalService.constBegin();
    while( it != mOptionalService.constEnd() )
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
    if( mState == PLUGIN_NOT_LOADED       ) return QStringLiteral( "Plugin not loaded." );
    if( mState == PLUGIN_NOT_LOADED_ERROR ) return QStringLiteral( "Plugin not loaded (errors occured)." );
    if( mState == PLUGIN_LOADED           ) return QStringLiteral( "Plugin loaded." );
    else                                    return QStringLiteral( "Plugin state unknown." );
}

const QStringList& HbPluginInfos::children() const
{
    return mChildren;
}

bool HbPluginInfos::requiresPlugin( const QString & name ) const
{
    return mRequiredPlugins.contains(name);
}

void HbPluginInfos::addRequiredPlugin( const QString & name, const QString & version )
{
    mRequiredPlugins[name] = version;
}

void HbPluginInfos::addOptionalPlugin( const QString & name, const QString & version )
{
    mOptionalPlugins[name] = version;
}

void HbPluginInfos::addRequiredService( const QString & name, const QString & version )
{
    mRequiredService[name] = version;
}

void HbPluginInfos::addOptionalService( const QString & name, const QString & version )
{
    mOptionalService[name] = version;
}

void HbPluginInfos::addChild( const QString & plugin_name )
{
    mChildren.append( plugin_name );
}
