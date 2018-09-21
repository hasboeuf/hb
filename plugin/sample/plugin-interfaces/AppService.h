#ifndef APPSERVICE_H
#define APPSERVICE_H

// Hb
#include <HbPluginService.h>

namespace hb {
namespace pluginexample {
using hb::plugin::HbPluginService;

class AppService : public HbPluginService {
    Q_OBJECT

public:
    explicit AppService(const QString& name, const QString& version);

protected:
};
} // namespace pluginexample
} // namespace hb

#endif // APPSERVICE_H
