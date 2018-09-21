/****************************************************************************
** Copyright (C) 2012-2015 Adrien Gavignet (hasboeuf)
** Contact: adrien.gavignet@gmail.com
**
** This file is part of the Hb module. Provided "AS IS", WITHOUT WARRANTIES
** OR CONDITIONS OF ANY KIND, either express or implied.
****************************************************************************/

#ifndef HBPLUGINLISTWIDGET_H
#define HBPLUGINLISTWIDGET_H

/*! \file HbPluginListWidget.h */

// Qt
#include <QtCore/QSortFilterProxyModel>
#include <QtCore/QStringList>
#include <QtGui/QStandardItemModel>
// Local
#include <HbPlugin.h>
#include <HbPluginInfos.h>
#include <ui_HbPluginListWidget.h>

namespace hb {
namespace plugin {
/*!
 * HbPluginListWidget is a widget to display HbPluginInfos in a convenient way.
 */
class HB_PLUGIN_DECL HbPluginListWidget : public QWidget, private Ui::HbPluginListWidget {
    Q_OBJECT

public:
    enum ColumnId { COLUMN_NAME = 0, COLUMN_LOAD, COLUMN_VERSION, COLUMN_AUTHOR, COLUMN_REQUIRED, COLUMN_OPTIONAL };

    enum RoleId { ROLE_PLUGIN_NAME = Qt::UserRole, ROLE_PLUGIN_CHECKSTATE };

    explicit HbPluginListWidget(QWidget* parent = nullptr);

public slots:
    /*!
     * Fired when a plugin has changed its state.
     * From HbPluginPlatform.
     */
    void onPluginStateChanged(const HbPluginInfos& plugin_infos);

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

private:
    QStringList mLabels;
    QStandardItemModel mModel;
    QSortFilterProxyModel mProxy;

    QHash<QString, QStandardItem*> mPlugins;
};
} // namespace plugin
} // namespace hb

#endif // HBPLUGINLISTWIDGET_H
