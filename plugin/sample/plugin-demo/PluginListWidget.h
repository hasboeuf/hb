#ifndef PLUGINLISTWIDGET_H
#define PLUGINLISTWIDGET_H

/*! \file PluginListWidget.h */

// Qt
#include <QtCore/QSortFilterProxyModel>
#include <QtCore/QStringList>
#include <QtGui/QStandardItemModel>
// Local
#include <HbPluginInfo.h>
#include <ui_PluginListWidget.h>

using hb::plugin::HbPluginInfo;

namespace hb {
namespace pluginexample {
/*!
 * PluginListWidget is a widget to display HbPluginInfo in a convenient way.
 */
class PluginListWidget : public QWidget, private Ui::PluginListWidget {
    Q_OBJECT

public:
    enum ColumnId { COLUMN_NAME = 0, COLUMN_LOAD, COLUMN_VERSION, COLUMN_AUTHOR, COLUMN_REQUIRED, COLUMN_OPTIONAL };

    enum RoleId { ROLE_PLUGIN_NAME = Qt::UserRole, ROLE_PLUGIN_CHECKSTATE };

    explicit PluginListWidget(QWidget* parent = nullptr);

    /*!
     * Fired when a plugin has changed its state.
     * From HbPluginPlatform.
     */
    void onPluginStateChanged(const HbPluginInfo& plugin_info);

    /*!
     * Fired when a QStandardItemModel changed.
     * Internal.
     * \param item_load Pointer of the item.
     */
    void onPluginChecked(QStandardItem* item_load);

signals:
    /*!
     * Triggered when a plugin item got checked.
     * \param Plugin name.
     */
    void loadPluginRequest(const QString& plugin_name);
    /*!
     * Triggered when a plugin item got unchecked.
     * \param Plugin name.
     */
    void unloadPluginRequest(const QString& plugin_name);

private:
    QStandardItem* getLoadItem(const QString& plugin_name);

    QStringList mLabels;
    QStandardItemModel mModel;
    QSortFilterProxyModel mProxy;

    QHash<QString, QStandardItem*> mPlugins;
};
} // namespace pluginexample
} // namespace hb

#endif // PLUGINLISTWIDGET_H
