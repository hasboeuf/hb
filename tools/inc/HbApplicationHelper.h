#ifndef HBAPPLICATIONHELPER_H
#define HBAPPLICATIONHELPER_H

// Local
#include <HbTools.h>

namespace hb
{
	namespace tools
	{
		class HB_TOOLS_DECL HbApplicationHelper
		{

		public:
			static void initApp(const QString & company, const QString & domain, const QString & name = QString());
			static void initSkin(const QString & skin);
		};
	}
}

#endif // HBAPPLICATIONHELPER_H
