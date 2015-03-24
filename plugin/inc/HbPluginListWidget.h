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
#include <QtGui/QStandardItemModel>
#include <QtCore/QStringList>
#include <QtCore/QSortFilterProxyModel>
// Local
#include <ui_HbPluginListWidget.h>
#include <HbPluginInfos.h>
#include <HbPlugin.h>

namespace hb
{
    namespace plugin
    {
        /*!
         * TODOC
         */
        class HB_PLUGIN_DECL HbPluginListWidget : public QWidget, private Ui::HbPluginListWidget
        {
            Q_OBJECT

        public:
            enum ColumnID
            {
                COLUMN_NAME = 0,
                COLUMN_LOAD,
                COLUMN_VERSION,
                COLUMN_AUTHOR,
                COLUMN_REQUIRED,
                COLUMN_OPTIONAL
            };

            explicit HbPluginListWidget( QWidget * parent = nullptr );

            void setPlugins( QList< HbPluginInfos > plugins );

        private:
            QStandardItem * getLoadItem( const QString & plugin_name );

        private:

            QStringList           mLabels;

            QStandardItemModel    mModel;
            QSortFilterProxyModel mProxy;

            QHash<QString, QStandardItem*> mPlugins;

            public slots:
            // From PlatformService
            void onPluginLoaded  ( const HbPluginInfos & plugin_infos );
            void onPluginUnloaded( const HbPluginInfos & plugin_infos );

            // From Delegate
            void onPluginChecked( QStandardItem * item_load );

        signals:
            void loadPluginRequest  ( const QString & plugin_name );
            void unloadPluginRequest( const QString & plugin_name );
        };
    }
}

#endif // HBPLUGINLISTWIDGET_H
