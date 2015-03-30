/****************************************************************************
** Copyright (C) 2012-2015 Adrien Gavignet (hasboeuf)
** Contact: adrien.gavignet@gmail.com
**
** This file is part of the Hb module. Provided "AS IS", WITHOUT WARRANTIES
** OR CONDITIONS OF ANY KIND, either express or implied.
****************************************************************************/

#ifndef HBNETWORK_H
#define HBNETWORK_H

/*! \file HbNetwork.h */

/*! \namespace hb::network
 * Contains all classes relatives to networking.
 */

// Qt
#include <QtCore/QtGlobal>

// Com level
typedef quint32 networkuid;  //!< Integer range for socket/server uid.
typedef quint16 serviceuid;  //!< Integer range for service uid.
typedef quint16 codeuid;     //!< Integer range for code uid.
typedef quint64 contractuid; //!< Integer range for contract uid.
// High level
typedef quint8  authstgy; //!< Integer range for auth strategies.
typedef quint8  netwint;  //!< Integer range mainly for network enums.


const size_t CLASS_SOCKET   = 20; //!< Identifier for socket uids class.
const size_t CLASS_SERVER   = 21; //!< Identifier for server uids class.
const size_t CLASS_CONTRACT = 22; //!< Identifier for contract uids class.

#if !defined( HB_NETWORK_DECL )
#    if defined( HB_NETWORK_BUILD )
#        define HB_NETWORK_DECL Q_DECL_EXPORT
#    else
#        define HB_NETWORK_DECL Q_DECL_IMPORT
#    endif
#endif

#endif // HBNETWORK_H
