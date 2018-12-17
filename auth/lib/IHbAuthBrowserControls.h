#ifndef IHBAUTHBROWSERCONTROLS_H
#define IHBAUTHBROWSERCONTROLS_H

// Qt
#include <QtCore/QUrl>
// Hb
#include <HbAuth.h>

namespace hb {
namespace auth {

class HB_AUTH_DECL IHbAuthBrowserControls {
public:
    virtual void onOpenBrowser(const QUrl& url) = 0;
    virtual void onCloseBrowser() = 0;
};
} // namespace auth
} // namespace hb

#endif // IHBAUTHBROWSERCONTROLS_H
