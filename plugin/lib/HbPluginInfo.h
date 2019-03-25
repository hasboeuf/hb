#ifndef HBPLUGININFO_H
#define HBPLUGININFO_H

/*! \file HbPluginInfo.h */

// Qt
#include <QtCore/QHash>
#include <QtCore/QSet>
#include <QtCore/QString>
// Hb
#include <core/HbEnum.h>
// Local
#include <HbPlugin.h>

namespace hb {
namespace plugin {
/*!
 * HbPluginInfo represents plugin informations.
 * It stores all informations to correctly identify and use a plugin:
 * path, name, version, author, dependencies and children.
 */
class HB_PLUGIN_DECL HbPluginInfo : public QObject {
    Q_OBJECT

public:
    enum PluginState {
        PLUGIN_NOT_REGISTERED,
        PLUGIN_REGISTERED,
        PLUGIN_CHANGING, // Transition when plugin is un/loading.
        PLUGIN_LOADED_PARTIALLY,
        PLUGIN_LOADED
    };
    Q_ENUM(PluginState)
    HB_ENUM(PluginState)

    HbPluginInfo(QObject* parent = nullptr);
    ~HbPluginInfo();

    void setPath(const QString& path);
    void setAuthor(const QString& author);
    void setName(const QString& name);
    void setVersion(const QString& version);
    void setState(PluginState state);

    bool isLoaded() const;

    QString path() const;
    QString author() const;
    QString name() const;
    QString version() const;
    const QHash<QString, QString>& requiredPlugins() const;
    QString requiredPluginsStr() const;
    const QHash<QString, QString>& optionalPlugins() const;
    QString optionalPluginsStr() const;
    const QHash<QString, QString>& requiredServices() const;
    QString requiredServicesStr() const;
    const QHash<QString, QString>& optionalServices() const;
    QString optionalServicesStr() const;
    HbPluginInfo::PluginState state() const;
    QString stateStr() const;
    const QSet<QString>& children() const;

    bool requiresPlugin(const QString& name) const;
    bool requiresService(const QString& name) const;

    void addRequiredPlugin(const QString& name, const QString& version);
    void addOptionalPlugin(const QString& name, const QString& version);
    void addRequiredService(const QString& name, const QString& version);
    void addOptionalService(const QString& name, const QString& version);

    void addChild(const QString& plugin_name);

signals:
    void stateChanged();

private:
    QString mPath;
    QString mAuthor;
    QString mName;
    QString mVersion;
    QHash<QString, QString> mRequiredPlugins;
    QHash<QString, QString> mOptionalPlugins;
    QHash<QString, QString> mRequiredService;
    QHash<QString, QString> mOptionalService;
    PluginState mState;

    QSet<QString> mChildren;
};
} // namespace plugin
} // namespace hb

#endif // HBPLUGININFO_H
