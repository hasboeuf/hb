/****************************************************************************
** Copyright (C) 2012-2015 Adrien Gavignet (hasboeuf)
** Contact: adrien.gavignet@gmail.com
**
** This file is part of the Hb module. Provided "AS IS", WITHOUT WARRANTIES
** OR CONDITIONS OF ANY KIND, either express or implied.
****************************************************************************/

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
