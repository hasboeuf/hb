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
 * TODOC
 */

// Qt
#include <QtCore/QtGlobal>

#if !defined( HB_PLUGIN_DECL )
#    if defined( HB_PLUGIN_BUILD )
#        define HB_PLUGIN_DECL Q_DECL_EXPORT
#    else
#        define HB_PLUGIN_DECL Q_DECL_IMPORT
#    endif
#endif

#endif // HBNETWORK_H
