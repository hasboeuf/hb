#ifndef HBNETWORK_H
#define HBNETWORK_H

// Qt
#include <QtCore/QtGlobal>

#if !defined( HB_NETWORK_DECL )
#	if defined( HB_NETWORK_BUILD )
#		define HB_NETWORK_DECL Q_DECL_EXPORT
#	else
#		define HB_NETWORK_DECL Q_DECL_IMPORT
#	endif
#endif

#endif // HBNETWORK_H