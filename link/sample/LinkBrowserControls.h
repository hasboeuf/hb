#ifndef LINKBROWSERCONTROLS_H
#define LINKBROWSERCONTROLS_H

// Qt
// Hb
#include <IHbLinkBrowserControls.h>

namespace hb
{
    namespace linkexample
    {

        class LinkBrowserControls : public link::IHbLinkBrowserControls
        {
            Q_OBJECT

        public slots:
            virtual void onOpenBrowser( const QUrl & url );
            virtual void onCloseBrowser();
        };
    }
}


#endif // LINKBROWSERCONTROLS_H
