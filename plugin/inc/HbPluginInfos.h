/****************************************************************************
** Copyright (C) 2012-2015 Adrien Gavignet (hasboeuf)
** Contact: adrien.gavignet@gmail.com
**
** This file is part of the Hb module. Provided "AS IS", WITHOUT WARRANTIES
** OR CONDITIONS OF ANY KIND, either express or implied.
****************************************************************************/

#ifndef HBPLUGININFOS_H
#define HBPLUGININFOS_H

/*! \file HbPluginInfos.h */

// Qt
#include <QtCore/QHash>
#include <QtCore/QString>
#include <QtCore/QStringList>
// Local
#include <HbPlugin.h>

namespace hb
{
    namespace plugin
    {
        /*!
         * TODOC
         */
        class HB_PLUGIN_DECL HbPluginInfos
        {
            enum PluginState
            {
                PLUGIN_NOT_LOADED,
                PLUGIN_NOT_LOADED_ERROR,
                PLUGIN_LOADED
            };

        public:
            HbPluginInfos(QString path, QString author, QString name, QString version);
            HbPluginInfos(const HbPluginInfos& copy);

            HbPluginInfos& operator=(const HbPluginInfos& copy);

            QString                          path() const;
            QString                          author() const;
            QString                          name() const;
            QString                          version() const;
            QHash<QString, QString>          requiredPlugins() const;
            QString                          requiredPluginsStr() const;
            QHash<QString, QString>          optionalPlugins() const;
            QString                          optionalPluginsStr() const;
            QHash<QString, QString>          requiredServices() const;
            QString                          requiredServicesStr() const;
            QHash<QString, QString>          optionalServices() const;
            QString                          optionalServicesStr() const;
            HbPluginInfos::PluginState         state() const;
            QString                          stateStr() const;
            const QStringList&               children() const;

            bool                     requiresPlugin(QString name) const;
            bool                     requiresService(QString name) const;

            void                     addRequiredPlugin(QString name, QString version);
            void                     addOptionalPlugin(QString name, QString version);
            void                     addRequiredService(QString name, QString version);
            void                     addOptionalService(QString name, QString version);

            void                     addChild(QString plugin_name);

        private:
            QString                   mPath;
            QString                   mAuthor;
            QString                   mName;
            QString                   mVersion;
            QHash<QString, QString>   mRequiredPlugins;
            QHash<QString, QString>   mOptionalPlugins;
            QHash<QString, QString>   mRequiredService;
            QHash<QString, QString>   mOptionalService;
            PluginState               mState;

            QStringList               mChildren;

        };
    }
}

#endif // HBPLUGININFOS_H
