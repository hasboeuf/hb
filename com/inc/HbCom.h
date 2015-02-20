/****************************************************************************
** Copyright (C) 2012-2015 Adrien Gavignet (hasboeuf)
** Contact: adrien.gavignet@gmail.com
**
** This file is part of the Hb module. Provided "AS IS", WITHOUT WARRANTIES
** OR CONDITIONS OF ANY KIND, either express or implied.
****************************************************************************/

#ifndef HBCOM_H
#define HBCOM_H

// Qt
#include <QtCore/QtGlobal>

typedef quint32 sockuid;
typedef quint16 netwuid;
typedef quint16 servuid;
typedef quint16 codeuid;
typedef quint64 ctctuid;

const size_t CLASS_SOCK = 20;
const size_t CLASS_NETW = 21;
const size_t CLASS_CTCT = 22;

#if !defined( HB_COM_DECL )
#    if defined( HB_COM_BUILD )
#        define HB_COM_DECL Q_DECL_EXPORT
#    else
#        define HB_COM_DECL Q_DECL_IMPORT
#    endif
#endif

#endif // HBCOM_H
