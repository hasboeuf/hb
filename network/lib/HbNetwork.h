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
typedef quint32 contractuid; //!< Integer range for contract uid.
// High level
typedef quint8 authstgy;  //!< Integer range for auth strategies.
typedef quint8 netwint;   //!< Integer range (8 bytes) mainly for network enums.
typedef quint16 netwlint; //!< Integer range (16 bytes) mainly for network enums.

const size_t CLASS_SOCKET = 20;   //!< Identifier for socket uids class.
const size_t CLASS_SERVER = 21;   //!< Identifier for server uids class.
const size_t CLASS_CONTRACT = 22; //!< Identifier for contract uids class.

// clang-format off
#if !defined( HB_NETWORK_DECL )
#   if defined( HB_SHARED )
#       if defined( HB_NETWORK_SHARED )
#           define HB_NETWORK_DECL Q_DECL_EXPORT
#       else
#           define HB_NETWORK_DECL Q_DECL_IMPORT
#       endif
#   else
#       define HB_NETWORK_DECL
#   endif
#endif
// clang-format on

#endif // HBNETWORK_H
