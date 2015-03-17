/****************************************************************************
** Copyright (C) 2012-2015 Adrien Gavignet (hasboeuf)
** Contact: adrien.gavignet@gmail.com
**
** This file is part of the Hb module. Provided "AS IS", WITHOUT WARRANTIES
** OR CONDITIONS OF ANY KIND, either express or implied.
****************************************************************************/

#ifndef HBNETWORK_H
#define HBNETWORK_H

/*! \file HbNetwork.h TODOC */

/*! \namespace hb::network
 * TODOC
 */

// Qt
#include <QtCore/QtGlobal>

// Com level
typedef quint32 networkuid;
typedef quint16 serviceuid;
typedef quint16 codeuid;
typedef quint64 contractuid;
// High level
typedef quint8  authstgy;
typedef quint8  netwint;


const size_t CLASS_SOCKET   = 20;
const size_t CLASS_SERVER   = 21;
const size_t CLASS_CONTRACT = 22;

#if !defined( HB_NETWORK_DECL )
#    if defined( HB_NETWORK_BUILD )
#        define HB_NETWORK_DECL Q_DECL_EXPORT
#    else
#        define HB_NETWORK_DECL Q_DECL_IMPORT
#    endif
#endif

#endif // HBNETWORK_H
