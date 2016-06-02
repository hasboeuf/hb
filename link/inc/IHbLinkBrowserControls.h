#ifndef IHBLINKBROWSERCONTROLS_H
#define IHBLINKBROWSERCONTROLS_H

// Qt
#include <QtCore/QObject>
// Hb
#include <HbLink.h>

namespace hb
{
    namespace link
    {

        class HB_LINK_DECL IHbLinkBrowserControls : public QObject
        {
            Q_OBJECT

        public slots:
            virtual void onOpenBrowser( const QUrl & url ) = 0;
            virtual void onCloseBrowser() = 0;
        };
    }
}


#endif // IHBLINKBROWSERCONTROLS_H
