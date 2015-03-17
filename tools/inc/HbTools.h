/****************************************************************************
** Copyright (C) 2012-2015 Adrien Gavignet (hasboeuf)
** Contact: adrien.gavignet@gmail.com
**
** This file is part of the Hb module. Provided "AS IS", WITHOUT WARRANTIES
** OR CONDITIONS OF ANY KIND, either express or implied.
****************************************************************************/

#ifndef HBTOOLS_H
#define HBTOOLS_H

/*! \file HbTools.h */

/*! \namespace hbprivate
 * TODOC
 */

/*! \namespace hb
 * TODOC
 */

/*! \namespace hb::tools
 * TODOC
 */

// Qt
#include <QtCore/QtGlobal>

/*! \typedef replyuid
 * Integer range for replies.
 */
typedef quint64 replyuid;

const size_t CLASS_DEFAULT = 0; //!< Default class identifier for uids.
const size_t CLASS_REPLIES = 10; //!< Identifier for replies uids class.

#if !defined( HB_TOOLS_DECL )
#   if defined( HB_TOOLS_BUILD )
#       define HB_TOOLS_DECL Q_DECL_EXPORT
#   else
#       define HB_TOOLS_DECL Q_DECL_IMPORT
#   endif
#endif


#endif // HBTOOLS_H
