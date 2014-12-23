// Qt
#include <QtCore/QDebug>
// Hb
#include <HbPluginListWidget.h>

using namespace hb::plugin;

HbPluginListWidget::HbPluginListWidget(QWidget *parent) :
    QWidget(parent)
{
    setupUi(this);

    mLabels.insert(COLUMN_NAME,         "Name");
    mLabels.insert(COLUMN_LOAD,         "Loaded");
    mLabels.insert(COLUMN_VERSION,      "Version");
    mLabels.insert(COLUMN_AUTHOR,       "Author");
    mLabels.insert(COLUMN_REQUIRED,     "Required");
    mLabels.insert(COLUMN_OPTIONAL,     "Optional");

    mModel.setHorizontalHeaderLabels(mLabels);
    mProxy.setSourceModel(&mModel);

    connect(&mModel, &QStandardItemModel::itemChanged, this, &HbPluginListWidget::onPluginChecked);

    qtv_plugins->setModel(&mProxy);
    qtv_plugins->setAlternatingRowColors(true);
    qtv_plugins->setSelectionBehavior(QAbstractItemView::SelectRows);
    qtv_plugins->setSelectionMode(QAbstractItemView::SingleSelection);
    qtv_plugins->verticalHeader()->hide();
    qtv_plugins->setEditTriggers(QAbstractItemView::NoEditTriggers);
    qtv_plugins->verticalHeader()->setDefaultSectionSize(20);
    qtv_plugins->setSortingEnabled(true);
}

void HbPluginListWidget::setPlugins(QList<const HbPluginInfos*> plugins)
{
    foreach(const HbPluginInfos* info, plugins)
    {
        if(info)
        {
            onPluginLoaded(info);
        }
    }
}

QStandardItem* HbPluginListWidget::getLoadItem(QString plugin_name)
{
    QStandardItem* item_name = mPlugins.value(plugin_name);
    if(!item_name)
    {
        return 0;
    }

    int row = item_name->row();

    return mModel.item(row, COLUMN_LOAD);
}


void HbPluginListWidget::onPluginLoaded  (const HbPluginInfos* plugin_infos)
{
    if(!plugin_infos) return;

    if(!mPlugins.contains(plugin_infos->name()))
    {
        QStandardItem* item_name         = new QStandardItem();
        QStandardItem* item_load         = new QStandardItem();
        QStandardItem* item_version      = new QStandardItem();
        QStandardItem* item_author       = new QStandardItem();
        QStandardItem* item_required     = new QStandardItem();
        QStandardItem* item_optional     = new QStandardItem();

        item_load->setCheckable(true);

        item_load->setFlags(item_load->flags() | Qt::ItemIsUserCheckable /*| Qt::ItemIsEditable*/);

        item_name->setData        (plugin_infos->name(),            Qt::DisplayRole);
        item_load->setData        (Qt::Checked,                     Qt::CheckStateRole);
        item_load->setData        (plugin_infos->name(),            Qt::UserRole); // To retrieve efficiently the name of the plugin when the checkbox is un/checked.
        item_version->setData     (plugin_infos->version(),         Qt::DisplayRole);
        item_author->setData      (plugin_infos->author(),          Qt::DisplayRole);
        item_required->setData(plugin_infos->requiredPluginsStr() + " " +
                                   plugin_infos->requiredServicesStr(), Qt::DisplayRole);
        item_optional->setData(plugin_infos->optionalPluginsStr() + " " +
                                   plugin_infos->optionalServicesStr(), Qt::DisplayRole);


        QList<QStandardItem*> plugin_row;
        plugin_row.append(item_name);
        plugin_row.append(item_load);
        plugin_row.append(item_version);
        plugin_row.append(item_author);
        plugin_row.append(item_required);
        plugin_row.append(item_optional);

        mPlugins.insert(plugin_infos->name(), item_name);

        mModel.appendRow(plugin_row);
    }
    else
    {
        QStandardItem* item_load = getLoadItem(plugin_infos->name());
        if(item_load)
        {
            disconnect(&mModel, &QStandardItemModel::itemChanged, this, &HbPluginListWidget::onPluginChecked);

            item_load->setData(Qt::Checked,                     Qt::CheckStateRole);

            connect(&mModel, &QStandardItemModel::itemChanged, this, &HbPluginListWidget::onPluginChecked);
        }
    }
}

void HbPluginListWidget::onPluginUnloaded(QString plugin_name)
{
    QStandardItem* item_load = getLoadItem(plugin_name);
    if(item_load)
    {
        disconnect(&mModel, &QStandardItemModel::itemChanged, this, &HbPluginListWidget::onPluginChecked);

        item_load->setData        (Qt::Unchecked,                   Qt::CheckStateRole);

        connect(&mModel, &QStandardItemModel::itemChanged, this, &HbPluginListWidget::onPluginChecked);
    }
}

void HbPluginListWidget::onPluginChecked  (QStandardItem* item_load)
{
    if(!item_load) return;

    QString plugin_name = item_load->data(Qt::UserRole).toString();

    disconnect(&mModel, &QStandardItemModel::itemChanged, this, &HbPluginListWidget::onPluginChecked);

    if(item_load->data(Qt::CheckStateRole).toInt() == Qt::Checked)
    {
        item_load->setData(Qt::Unchecked, Qt::CheckStateRole);
        emit loadPluginRequest(plugin_name);
    }
    else
    {
        item_load->setData(Qt::Checked, Qt::CheckStateRole);
        emit unloadPluginRequest(plugin_name);
    }

    connect(&mModel, &QStandardItemModel::itemChanged, this, &HbPluginListWidget::onPluginChecked);
}
