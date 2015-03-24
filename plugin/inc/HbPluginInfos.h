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
#include <QtCore/QSet>
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
        public:
            enum PluginState
            {
                PLUGIN_NOT_LOADED,
                PLUGIN_LOADED
            };


            HbPluginInfos();
            HbPluginInfos( const HbPluginInfos & copy );
            HbPluginInfos & operator=( const HbPluginInfos & copy );

            void setPath   ( const QString & path    );
            void setAuthor ( const QString & author  );
            void setName   ( const QString & name    );
            void setVersion( const QString & version );
            void setState  ( PluginState state );

            bool isLoaded() const;

            const QString &                  path               () const;
            const QString &                  author             () const;
            const QString &                  name               () const;
            const QString &                  version            () const;
            const QHash<QString, QString> &  requiredPlugins    () const;
            QString                          requiredPluginsStr () const;
            const QHash<QString, QString> &  optionalPlugins    () const;
            QString                          optionalPluginsStr () const;
            const QHash<QString, QString> &  requiredServices   () const;
            QString                          requiredServicesStr() const;
            const QHash<QString, QString> &  optionalServices   () const;
            QString                          optionalServicesStr() const;
            HbPluginInfos::PluginState       state              () const;
            QString                          stateStr           () const;
            const QSet< QString > &          children           () const;

            bool requiresPlugin ( const QString & name ) const;
            bool requiresService( const QString & name ) const;

            void addRequiredPlugin ( const QString & name, const QString & version );
            void addOptionalPlugin ( const QString & name, const QString & version );
            void addRequiredService( const QString & name, const QString & version );
            void addOptionalService( const QString & name, const QString & version );

            void addChild( const QString & plugin_name );

        private:
            QString                   mPath;
            QString                   mAuthor;
            QString                   mName;
            QString                   mVersion;
            QHash< QString, QString > mRequiredPlugins;
            QHash< QString, QString > mOptionalPlugins;
            QHash< QString, QString > mRequiredService;
            QHash< QString, QString > mOptionalService;
            PluginState               mState;

            QSet< QString >           mChildren;

        };
    }
}

#endif // HBPLUGININFOS_H
