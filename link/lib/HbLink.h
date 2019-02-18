#ifndef HBLINK_H
#define HBLINK_H

/*! \file HbLink.h */

/*! \namespace hb::link
 * Contains all classes relatives to oauth authentication.
 */

// clang-format off
#if !defined( HB_LINK_DECL )
#   if defined( HB_SHARED )
#       if defined( HB_LINK_SHARED )
#           define HB_LINK_DECL Q_DECL_EXPORT
#       else
#           define HB_LINK_DECL Q_DECL_IMPORT
#       endif
#   else
#       define HB_LINK_DECL
#   endif
#endif
// clang-format on

#endif // HBLINK_H
