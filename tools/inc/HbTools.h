#ifndef HBTOOLS_H
#define HBTOOLS_H

// Qt
#include <QtCore/QtGlobal>

#if !defined( HB_TOOLS_DECL )
#   if defined( HB_TOOLS_BUILD )
#       define HB_TOOLS_DECL Q_DECL_EXPORT
#   else
#       define HB_TOOLS_DECL Q_DECL_IMPORT
#   endif
#endif


#endif // HBTOOLS_H
