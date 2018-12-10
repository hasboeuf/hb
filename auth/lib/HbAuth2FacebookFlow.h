#ifndef HBAUTH2FACEBOOKFLOW_H
#define HBAUTH2FACEBOOKFLOW_H

// Local
#include <HbAuth2Flow.h>

namespace hb {
namespace auth {
class HbAuth2FacebookFlow : public HbAuth2Flow {
public:
    HbAuth2FacebookFlow(QNetworkAccessManager* networkAccessManager, QObject* parent = nullptr);
};
} // namespace auth
} // namespace hb

#endif // HBAUTH2FACEBOOKFLOW_H
