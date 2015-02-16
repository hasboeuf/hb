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

typedef quint32 sockuuid;
typedef quint16 netwuuid;
typedef quint16 servuuid;
typedef quint16 authstgy;
typedef quint32 kickcode;
typedef quint16 netwcode;
typedef quint64 ctctuuid;

const size_t CLASS_SOCK = 20;
const size_t CLASS_NETW = 21;
const size_t CLASS_SERV = 22;
const size_t CLASS_CTCT = 23;

#if !defined( HB_NETWORK_DECL )
#	if defined( HB_NETWORK_BUILD )
#		define HB_NETWORK_DECL Q_DECL_EXPORT
#	else
#		define HB_NETWORK_DECL Q_DECL_IMPORT
#	endif
#endif

#endif // HBNETWORK_H
