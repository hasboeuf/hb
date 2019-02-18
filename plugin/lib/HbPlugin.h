#ifndef HBPLUGIN_H
#define HBPLUGIN_H

/*! \file HbPlugin.h */

/*! \namespace hb::plugin
 * Contains all classes relatives to plugin management.
 */

// Qt
#include <QtCore/QtGlobal>

// clang-format off
#if !defined( HB_PLUGIN_DECL )
#   if defined( HB_SHARED )
#       if defined( HB_PLUGIN_SHARED )
#           define HB_PLUGIN_DECL Q_DECL_EXPORT
#       else
#           define HB_PLUGIN_DECL Q_DECL_IMPORT
#       endif
#   else
#       define HB_PLUGIN_DECL
#   endif
#endif
// clang-format on

#endif // HBNETWORK_H
