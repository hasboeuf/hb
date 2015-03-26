/****************************************************************************
** Copyright (C) 2012-2015 Adrien Gavignet (hasboeuf)
** Contact: adrien.gavignet@gmail.com
**
** This file is part of the Hb module. Provided "AS IS", WITHOUT WARRANTIES
** OR CONDITIONS OF ANY KIND, either express or implied.
****************************************************************************/

#ifndef IHBPLUGIN_H
#define IHBPLUGIN_H

/*! \file IHbPlugin.h */

// Qt
#include <QtCore/QtPlugin>
#include <QtCore/QPluginLoader>
#include <QtGui/QIcon>
// Local
#include <HbPlatformService.h>
#include <HbPlugin.h>

namespace hb
{
    namespace plugin
    {
        /*!
         * IHbPlugin is the interface that every plugin must implement.
         */
        class HB_PLUGIN_DECL IHbPlugin
        {
        public:

            enum PluginInitState
            {
                INIT_SUCCESS,
                INIT_SUCCESS_PARTLY,
                INIT_FAIL
            };

            IHbPlugin() = default;
            virtual ~IHbPlugin() = default;

            /*!
             * Init plugin.
             * Called by HbPluginManager just after QPluginLoader finished to load the library.
             * \param platform_service Platform service, useful to request a plugin/service.
             *        TODO hide load/unload plugin features.
             * \return INIT_SUCCESS: all good.
             *         INIT_SUCCESS_PARTLY: optional services/plugins are missing.
             *         INIT_FAIL: not good, should be unloaded.
             */
            virtual PluginInitState init( const HbPlatformService * platform_service ) = 0;

            /*!
             * Terminate plugin.
             * Called by HbPluginManager just before QPluginLoader unloads the library.
             */
            virtual void unload() = 0;

        };
    }
}

Q_DECLARE_INTERFACE( hb::plugin::IHbPlugin, "hb::plugin::IHbPlugin" )

#endif // IHBPLUGIN_H
