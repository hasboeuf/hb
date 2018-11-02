/****************************************************************************
** Copyright (C) 2012-2015 Adrien Gavignet (hasboeuf)
** Contact: adrien.gavignet@gmail.com
**
** This file is part of the Hb module. Provided "AS IS", WITHOUT WARRANTIES
** OR CONDITIONS OF ANY KIND, either express or implied.
****************************************************************************/

#ifndef HBAUTH_H
#define HBAUTH_H

/*! \file HbAuth.h */

/*! \namespace hb::auth
 * Contains all classes relatives to oauth authentication.
 */

// clang-format off
#if !defined( HB_AUTH_DECL )
#   if defined( HB_SHARED )
#       if defined( HB_AUTH_SHARED )
#           define HB_AUTH_DECL Q_DECL_EXPORT
#       else
#           define HB_AUTH_DECL Q_DECL_IMPORT
#       endif
#   else
#       define HB_AUTH_DECL
#   endif
#endif
// clang-format on

namespace hb {
namespace auth {
void init();
}
} // namespace hb

#endif // HBAUTH_H
