/****************************************************************************
** Copyright (C) 2012-2015 Adrien Gavignet (hasboeuf)
** Contact: adrien.gavignet@gmail.com
**
** This file is part of the Hb module. Provided "AS IS", WITHOUT WARRANTIES
** OR CONDITIONS OF ANY KIND, either express or implied.
****************************************************************************/

#ifndef HBPLUGINMANAGER_H
#define HBPLUGINMANAGER_H

/*! \file HbPluginManager.h */

// Qt
#include <QtCore/QObject>
#include <QtCore/QHash>
// Local
#include <HbPluginInfos.h>
#include <HbPlugin.h>

class QPluginLoader;

namespace hb
{
    namespace plugin
    {
        class IHbPlugin;
        class HbPluginPlatform;

        /*!
         * HbPluginManager handles plugins.
         * Scan folders, seek for libraries, load plugins.
         */
        class HB_PLUGIN_DECL HbPluginManager : public QObject
        {
            Q_OBJECT
        public:
            explicit HbPluginManager( HbPluginPlatform * platformService, QObject * parent = nullptr );

            /*!
             * Load plugin contained in folder path.
             * \param folder_path Folder path.
             */
            void load  ( const QString & folder_path );

            /*!
             * Unload all plugins previously loaded.
             */
            void unload();

            /*!
             * Load a specific plugin.
             * \param plugin_path Path to the library to load.
             */
            void loadPluginFromPath( const QString & plugin_path );

            /*!
             * Load a specific plugin.
             * \param plugin_name Plugin name.
             */
            void loadPluginFromName( const QString & plugin_name );
            /*!
             * Unload a specific plugin.
             * \param plugin_name Plugin name.
             */
            void unloadPlugin      ( const QString & plugin_name );

            /*!
             * Get a specific plugin.
             * \param plugin_name Plugin name.
             */
            IHbPlugin * plugin( const QString & plugin_name ) const;

            /*!
             * Return previously scanned plugins infos.
             * \return Plugin infos list.
             */
            QList< HbPluginInfos > pluginInfoList();

        signals:
            /*!
             * Triggered when the state has changed.
             * To HbPluginManager.
             */
            void pluginStateChanged  ( const HbPluginInfos & plugin_infos );

        public slots:
            void onPluginStateChanged();

        private:
            void           scanFolder( const QString & folder_path );
            HbPluginInfos* scanPlugin( const QString & plugin_path );
            bool           loadPlugin( const QString & plugin_name );

        private:
            HbPluginPlatform * mpPlatformService;

            QString mPath;

            QHash< QString, HbPluginInfos * >     mPluginsInfos;
            QHash< QString, QPluginLoader * >     mPluginsLoaders;
            QHash< QString, IHbPlugin * >         mPlugins;

        };
    }
}

#endif // HBPLUGINMANAGER_H
