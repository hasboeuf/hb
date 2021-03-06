#ifndef HBLOG_H
#define HBLOG_H

/*! \file HbLog.h */

/*! \namespace hb::log
 * Contains all classes relatives to logging.
 */

// Qt
#include <QtCore/QSharedPointer>
#include <QtCore/QtGlobal>

typedef quint32 loguid; //!< Integer range for log in/outputs.

namespace hb {
namespace log {
class HbLogMessage;
using HbLogMessagePtr = QSharedPointer<HbLogMessage>;
} // namespace log
} // namespace hb

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
