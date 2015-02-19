/****************************************************************************
** Copyright (C) 2012-2015 Adrien Gavignet (hasboeuf)
** Contact: adrien.gavignet@gmail.com
**
** This file is part of the Hb module. Provided "AS IS", WITHOUT WARRANTIES
** OR CONDITIONS OF ANY KIND, either express or implied.
****************************************************************************/

#ifndef HBPLUGININTERFACE_H
#define HBPLUGININTERFACE_H

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
        class HB_PLUGIN_DECL HbPluginInterface
        {
        public:

            enum PluginInitState
            {
                INIT_SUCCESS,
                INIT_SUCCESS_PARTLY,
                INIT_FAIL
            };


            virtual ~HbPluginInterface();

            virtual PluginInitState init(const HbPlatformService * platform_service) = 0;
            virtual void unload() = 0;

        };
    }
}

Q_DECLARE_INTERFACE(hb::plugin::HbPluginInterface, "hb::plugin::HbPluginInterface")

#endif // HBPLUGININTERFACE_H
