#ifndef APPSERVICE_H
#define APPSERVICE_H

// Hb
#include <HbPluginService.h>

namespace hb
{
    namespace pluginexample
    {
        using hb::plugin::HbPluginService;

        class AppService : public HbPluginService
        {
            Q_OBJECT

        public:

            explicit AppService(QString name, QString version);

        protected:

        };
    }
}

#endif // APPSERVICE_H
