// Local
#include <HbAuth.h>
// Qt
#include <QtCore/qglobal.h>

inline void initHbAuth() {
    Q_INIT_RESOURCE(HbAuth);
}

void hb::auth::init() {
    initHbAuth();
}
