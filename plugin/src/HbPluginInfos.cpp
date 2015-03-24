// Qt
#include <QtCore/QDebug>
// Local
#include <HbPluginInfos.h>

using namespace hb::plugin;

HbPluginInfos::HbPluginInfos()
{
    mState   = PLUGIN_NOT_LOADED;
}

HbPluginInfos::HbPluginInfos( const HbPluginInfos & copy )
{
    if ( this != &copy )
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
}

HbPluginInfos& HbPluginInfos::operator=( const HbPluginInfos & copy )
{
    if ( this != &copy )
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

    return ( *this );
}

void HbPluginInfos::setPath   ( const QString & path    )
{
    mPath = path;
}

void HbPluginInfos::setAuthor ( const QString & author  )
{
    mAuthor = author;
}

void HbPluginInfos::setName   ( const QString & name    )
{
    mName = name;
}

void HbPluginInfos::setVersion( const QString & version )
{
    mVersion = version;
}

void HbPluginInfos::setState( PluginState state )
{
    mState = state;
}

bool HbPluginInfos::isLoaded() const
{
    return ( mState == PLUGIN_LOADED );
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

const QSet< QString > & HbPluginInfos::children() const
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
    mChildren.insert( plugin_name );
}
