#ifndef HBGLOBAL_H
#define HBGLOBAL_H

/*! \file HbGlobal.h
 * This file contains all useful macros used by HB module.
 */

// Qt
#include <QtCore/QString>

//! Check compilator compatibility.
// clang-format off
#if defined( Q_OS_WIN32 ) || defined( Q_OS_WINPHONE) || defined ( Q_OS_WINRT )
#   if !defined( Q_CC_MSVC ) && !defined( Q_CC_MINGW )
#   error Windows compiler not supported
#   endif
#elif defined( Q_OS_ANDROID ) || defined( Q_OS_LINUX )
#   include <linux/version.h>
#   if LINUX_VERSION_CODE < KERNEL_VERSION( 2, 6, 16 )
#   error Linux kernel version not supported
#   endif
#   if !defined( Q_CC_GNU )
#   error Linux compiler not supported
#   endif
#else
#error Operating system not supported
#endif
// clang-format on

//! GCC specifics.
#if defined(Q_CC_GNU) || defined(Q_CC_MINGW)
#include <cxxabi.h>
#include <typeinfo>
#endif

/*!
 * Convenient macro to declare a static class.
 */
#define Q_STATIC_CLASS(Class) \
    Class() Q_DECL_EQ_DELETE; \
    Class(const Class&) Q_DECL_EQ_DELETE; \
    Class& operator=(const Class&) Q_DECL_EQ_DELETE; \
    virtual ~Class() Q_DECL_EQ_DELETE;

#endif // HBGLOBAL_H
