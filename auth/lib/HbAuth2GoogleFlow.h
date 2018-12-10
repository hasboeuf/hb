#ifndef HBAUTH2GOOGLEFLOW_H
#define HBAUTH2GOOGLEFLOW_H

// Local
#include <HbAuth2Flow.h>

namespace hb {
namespace auth {
class HbAuth2GoogleFlow : public HbAuth2Flow {
public:
    HbAuth2GoogleFlow(QNetworkAccessManager* networkAccessManager, QObject* parent = nullptr);
};
} // namespace auth
} // namespace hb

#endif // HBAUTH2GOOGLEFLOW_H
