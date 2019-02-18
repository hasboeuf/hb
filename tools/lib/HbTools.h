#ifndef HBTOOLS_H
#define HBTOOLS_H

/*! \file HbTools.h */

/*! \namespace hb
 * Base namespace of HB module.
 */

/*! \namespace hbprivate
 * Private area of HB module, not supposed to be used by a third.
 */

/*! \namespace hb::tools
 * Contains all tools classes.
 */

// Qt
#include <QtCore/QtGlobal>

const size_t CLASS_DEFAULT = 0;  //!< Default class identifier for uids.
const size_t CLASS_REPLIES = 10; //!< Identifier for replies uids class.
const size_t CLASS_USER = 100;   //!< User class identifiers can begin from this value.

// clang-format off
#if !defined( HB_TOOLS_DECL )
#   if defined( HB_SHARED )
#       if defined( HB_TOOLS_SHARED )
#           define HB_TOOLS_DECL Q_DECL_EXPORT
#       else
#           define HB_TOOLS_DECL Q_DECL_IMPORT
#       endif
#   else
#       define HB_TOOLS_DECL
#   endif
#endif
// clang-format on

#endif // HBTOOLS_H
