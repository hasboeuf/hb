#ifndef HBAPPLICATIONHELPER_H
#define HBAPPLICATIONHELPER_H

/*! \file HbApplicationHelper.h */

// Qt
#include <QtCore/QSettings>
// Local
#include <HbTools.h>

namespace hb {
namespace tools {
/*!
 * HbApplicationHelper provides helper methods for QApplication.
 */
class HB_TOOLS_DECL HbApplicationHelper {
public:
    /*!
     * Initialize app.
     *
     * Set domain, company, app name.
     * Generate seed for qsrand.
     * Call it in main().
     * \param company Company name e.g.: MyCompany
     * \param domain Domain name e.g.: mycompany.io
     * \param name Application name e.g.: MyApp, by default it is the executable name.
     */
    static void initApp(const QString& company, const QString& domain, const QString& name = QString());

    /*!
     * Set the look and feel of the app.
     * Colors used are personal taste. HbLogo.png is set as window icon.
     * Call it in main().
     * \param skin Name of the style used in QStyleFactory.
     */
    static void initSkin(const QString& skin);

    /*!
     * Catch OS interrupting events and quit Qt application properly.
     * \note OS specific.
     * \todo Not tested on all platform.
     */
    static void catchInterruptingEvents();
};
} // namespace tools
} // namespace hb

#endif // HBAPPLICATIONHELPER_H
