#ifndef HBLOG_H
#define HBLOG_H

// Qt
#include <QtCore/QtGlobal>

#if !defined( HB_LOG_DECL )
#	if defined( HB_LOG_BUILD )
#		define HB_LOG_DECL Q_DECL_EXPORT
#	else
#		define HB_LOG_DECL Q_DECL_IMPORT
#	endif
#endif

#endif // HBLOG_H