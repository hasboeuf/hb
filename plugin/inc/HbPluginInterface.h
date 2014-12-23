#ifndef HBPLUGININTERFACE_H
#define HBPLUGININTERFACE_H

// Copyright (C) 2012-2014
// Adrien Gavignet (hasboeuf)
// adrien.gavignet@gmail.com

// Qt
#include <QtCore/QtPlugin>
#include <QtCore/QPluginLoader>
#include <QtGui/QIcon>
// Local
#include <HbPlatformService.h>

namespace hb
{
	namespace plugin
	{
		class HbPluginInterface
		{
		public:

			enum PluginInitState
			{
				INIT_SUCCESS,
				INIT_SUCCESS_PARTLY,
				INIT_FAIL
			};


			virtual ~HbPluginInterface();

			virtual PluginInitState init(const HbPlatformService* platform_service) = 0;
			virtual void            unload() = 0;

		};
	}
}

Q_DECLARE_INTERFACE(hb::plugin::HbPluginInterface, "HbPluginInterface")

#endif // HBPLUGININTERFACE_H
