/****************************************************************************
** Copyright (C) 2012-2015 Adrien Gavignet (hasboeuf)
** Contact: adrien.gavignet@gmail.com
**
** This file is part of the Hb module. Provided "AS IS", WITHOUT WARRANTIES
** OR CONDITIONS OF ANY KIND, either express or implied.
****************************************************************************/

#ifndef HBNETWORK_H
#define HBNETWORK_H

// Qt
#include <QtCore/QtGlobal>

// Com level
typedef quint32 sockuid;
typedef quint16 netwuid;
typedef quint16 servuid;
typedef quint16 codeuid;
typedef quint64 ctctuid;
// High level
typedef quint8  authstgy;
typedef quint8  netwint;

const size_t CLASS_SOCK = 20;
const size_t CLASS_NETW = 21;
const size_t CLASS_CTCT = 22;

#if !defined( HB_NETWORK_DECL )
#    if defined( HB_NETWORK_BUILD )
#        define HB_NETWORK_DECL Q_DECL_EXPORT
#    else
#        define HB_NETWORK_DECL Q_DECL_IMPORT
#    endif
#endif

#endif // HBNETWORK_H
