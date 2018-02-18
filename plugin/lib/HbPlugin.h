/****************************************************************************
** Copyright (C) 2012-2015 Adrien Gavignet (hasboeuf)
** Contact: adrien.gavignet@gmail.com
**
** This file is part of the Hb module. Provided "AS IS", WITHOUT WARRANTIES
** OR CONDITIONS OF ANY KIND, either express or implied.
****************************************************************************/

#ifndef HBPLUGIN_H
#define HBPLUGIN_H

/*! \file HbPlugin.h */

/*! \namespace hb::plugin
 * Contains all classes relatives to plugin management.
 */

// Qt
#include <QtCore/QtGlobal>

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

#endif // HBNETWORK_H