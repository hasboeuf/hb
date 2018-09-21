/****************************************************************************
** Copyright (C) 2012-2015 Adrien Gavignet (hasboeuf)
** Contact: adrien.gavignet@gmail.com
**
** This file is part of the Hb module. Provided "AS IS", WITHOUT WARRANTIES
** OR CONDITIONS OF ANY KIND, either express or implied.
****************************************************************************/

#ifndef HBLOG_H
#define HBLOG_H

/*! \file HbLog.h */

/*! \namespace hb::log
 * Contains all classes relatives to logging.
 */

// Qt
#include <QtCore/QtGlobal>
#include <QtCore/QSharedPointer>

typedef quint32 loguid; //!< Integer range for log in/outputs.

namespace hb {
namespace log {
    class HbLogMessage;
    using HbLogMessagePtr = QSharedPointer<HbLogMessage>;
}
}

const size_t CLASS_LOG = 30; //!< Identifier for log in/output uids class.

// clang-format off
#if !defined( HB_LOG_DECL )
#   if defined( HB_SHARED )
#       if defined( HB_LOG_SHARED )
#           define HB_LOG_DECL Q_DECL_EXPORT
#       else
#           define HB_LOG_DECL Q_DECL_IMPORT
#       endif
#   else
#       define HB_LOG_DECL
#   endif
#endif
// clang-format on

#endif // HBLOG_H
