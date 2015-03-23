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
        class HbPluginInterface;
        class HbPlatformService;

        /*!
         * TODOC
         */
        class HB_PLUGIN_DECL HbPluginManager : public QObject
        {
            Q_OBJECT
        public:
            explicit HbPluginManager( HbPlatformService * platformService, QObject * parent = nullptr );

            void load  ( const QString & folder_path );
            int  unload();

            void loadPluginFromPath( const QString & plugin_path);
            void loadPluginFromName( const QString & plugin_name);
            void unloadPlugin      ( const QString & plugin_name, bool clear = true );

            QHash< QString, QString > mLoadedPlugins; // Name Version.

            HbPluginInterface* plugin( const QString & name) const;

            const QList< const HbPluginInfos * > pluginInfoList();

        private:
            void           scanFolder( const QString & folder_path );
            HbPluginInfos* scanPlugin( const QString & plugin_path );
            bool           loadPlugin( const QString & name, const HbPluginInfos * child = nullptr );

        signals:
            void pluginLoaded       ( const HbPluginInfos * plugin_infos );
            void pluginLoadingFailed( const HbPluginInfos * plugin_infos );
            void pluginUnloaded     ( const QString &       plugin_name  );

            public slots:


        private:
            HbPlatformService * mpPlatformService;

            QString mPath;

            QHash< QString, HbPluginInfos * >     mPluginsInfos;
            QHash< QString, QPluginLoader * >     mPluginsLoaders;
            QHash< QString, HbPluginInterface * > mPlugins;

        };
    }
}

#endif // HBPLUGINMANAGER_H
