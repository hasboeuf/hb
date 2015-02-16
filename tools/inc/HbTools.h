/****************************************************************************
** Copyright (C) 2012-2015 Adrien Gavignet (hasboeuf)
** Contact: adrien.gavignet@gmail.com
**
** This file is part of the Hb module. Provided "AS IS", WITHOUT WARRANTIES
** OR CONDITIONS OF ANY KIND, either express or implied.
****************************************************************************/

#ifndef HBTOOLS_H
#define HBTOOLS_H

// Qt
#include <QtCore/QtGlobal>

typedef quint64 replyuuid;

const size_t CLASS_DEFAULT = 0;
const size_t CLASS_REPLIES = 10;

#if !defined( HB_TOOLS_DECL )
#   if defined( HB_TOOLS_BUILD )
#       define HB_TOOLS_DECL Q_DECL_EXPORT
#   else
#       define HB_TOOLS_DECL Q_DECL_IMPORT
#   endif
#endif


#endif // HBTOOLS_H
