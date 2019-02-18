#ifndef HBSTRINGHELPER_H
#define HBSTRINGHELPER_H

/*! \file HbStringHelper.h */

// Hb
#include <QtCore/QString>
// Local
#include <HbTools.h>

namespace hb {
namespace tools {
/*!
 * HbStringHelper provides helper methods for strings.
 */
class HB_TOOLS_DECL HbStringHelper {
public:
    /*!
     * Create a lower and upper alpha random string.
     * \param length Size of the generated string.
     */
    static QString randomString(quint32 string_length);
};
} // namespace tools
} // namespace hb

#endif // HBSTRINGHELPER_H
