/****************************************************************************
** Copyright (C) 2012-2015 Adrien Gavignet (hasboeuf)
** Contact: adrien.gavignet@gmail.com
**
** This file is part of the Hb module. Provided "AS IS", WITHOUT WARRANTIES
** OR CONDITIONS OF ANY KIND, either express or implied.
****************************************************************************/

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

//! Android specifics.
#if defined(Q_OS_ANDROID)
#define Q_OS_MOBILE
#endif

//! GCC specifics.
#if defined(Q_CC_GNU) || defined(Q_CC_MINGW)
#include <cxxabi.h>
#include <typeinfo>
#endif

/*!
 * Convenient macro for qt_assert use.
 */
#if !defined(QT_NO_DEBUG)
#define q_assert(test) ((test) ? qt_noop() : qt_assert(#test, __FILE__, __LINE__))
#else
#define q_assert(test) ((test) ? qt_noop() : qt_noop())
#endif

/*!
 * Convenient macro for qt_assert_x use.
 */
#if !defined(QT_NO_DEBUG)
#define q_assert_x(test, where, what) ((test) ? qt_noop() : qt_assert_x(where, what, __FILE__, __LINE__))
#else
#define q_assert_x(test, where, what) ((test) ? qt_noop() : qt_noop())
#endif

/*!
 * Convenient macro used to convert QString into const char * (\0 terminated).
 */
#if !defined(HbLatin1)
#define HbLatin1(string) QString(string).toLatin1().constData()
#endif

namespace // Anonymous.
{
/*!
 * TODOC
 */
inline QString hb_scopename(const char* type) {
#if defined(Q_CC_MSVC)
    QString name;
    name = QLatin1String(type);
#elif defined(Q_CC_GNU) || defined(Q_CC_MINGW)
    QString name;
    qint32 status = 0;

    char* demangled = abi::__cxa_demangle(type, nullptr, nullptr, &status);

    Q_ASSERT(status == 0);

    name = QLatin1String(demangled);
    free(demangled);
#endif
    return name;
}

/*!
 * TODOC
 */
inline QString hb_typename(const char* type) {
    QString name(hb_scopename(type));

    if (!name.isEmpty()) {
        qint32 truncate = 0;

        if ((truncate = name.lastIndexOf(QLatin1String(" *"))) > 0)
            name.truncate(truncate);

        if ((truncate = name.lastIndexOf(QChar::Space)) > 0)
            name = name.right(name.length() - (truncate + 1));

        if ((truncate = name.lastIndexOf(QLatin1Char(':'))) > 0)
            name = name.right(name.length() - (truncate + 1));
    }

    return name;
}
} // namespace

/*!
 * TODOC
 */
template <typename T> inline QString qScopeName() {
    return hb_scopename(typeid(T).name());
}

/*!
 * TODOC
 */
template <typename T> inline QString qScopeName(T* pointer) {
    return (pointer) ? hb_scopename(typeid(*pointer).name()) : QString();
}

/*!
 * TODOC
 */
template <typename T> inline QString qScopeName(const T& expression) {
    return hb_scopename(typeid(expression).name());
}

/*!
 * TODOC
 */
template <typename T> inline QString qTypeName() {
    return hb_typename(typeid(T).name());
}

/*!
 * TODOC
 */
template <typename T> inline QString qTypeName(T* pointer) {
    return (pointer) ? hb_typename(typeid(*pointer).name()) : QString();
}

/*!
 * TODOC
 */
template <typename T> inline QString qTypeName(const T& expression) {
    return hb_typename(typeid(expression).name());
}

namespace // Anonymous
{

/*!
 * TODOC
 */
template <typename T> inline T* hb_assert_ptr(T* pointer, const char* file, qint32 line) {
#if !defined(QT_NO_DEBUG)
    if (!pointer)
        qFatal("Null %s pointer detected in file %s, line %d", HbLatin1(qScopeName<T>()), file, line);
#else
    Q_UNUSED(file);
    Q_UNUSED(line);
#endif
    return pointer;
}

/*!
 * TODOC
 */
template <typename U, typename T> inline U hb_dynamic_cast(T* pointer, const char* file, qint32 line) {
#if !defined(QT_NO_DEBUG)

    U ptr_cast = dynamic_cast<U>(pointer);

    if (pointer && !ptr_cast) {
        qFatal("Invalid %s pointer cast detected in file %s, line %d", HbLatin1(qScopeName<U>()), file, line);
    }

    return ptr_cast;

#else
    Q_UNUSED(file);
    Q_UNUSED(line);

    return dynamic_cast<U>(pointer);
#endif
}

} // namespace

/*!
 * Convenient macro to assert a pointer.
 */
#define q_assert_ptr(pointer) hb_assert_ptr(pointer, __FILE__, __LINE__)

/*!
 * Convenient macro to dynamic cast a pointer.
 */
#define q_dynamic_cast(Type, pointer) hb_dynamic_cast<Type>(pointer, __FILE__, __LINE__)

/*!
 * Convenient function to dynamic cast an entire list of pointers.
 */
template <typename U, typename T> inline QList<U> qlist_dynamic_cast(const QList<T*>& list) {
    QList<U> list_cast;

    for (T* item : list)
        list_cast.append(q_dynamic_cast(U, item));

    return list_cast;
}

/*!
 * Convenient function to delete a pointer (reset nullptr).
 */
template <typename T> inline void q_delete_ptr(T** pointer) {
    delete *pointer;
    *pointer = nullptr;
}

/*!
 * Convenient macro to scope a method used as a slot by using the new Qt5 connect syntax.
 * class Object
 * {
 * public slots:
 *     void myQt4Slot();
 * public callbacks:
 *     void myQt5Slot();
 * };
 */
#define callbacks

/*!
 * Convenient macro to tag an inner class.
 * class Car
 * {
 *     inner class Engine
 *     {
 *     };
 * };
 */
#define inner

/*!
 * Convenient macro to declare a defaulted copyable class.
 */
#define Q_DEFAULT_COPY(Class) \
public: \
    Class(const Class&) Q_DECL_EQ_DEFAULT; \
    Class& operator=(const Class&) Q_DECL_EQ_DEFAULT; \
\
private:

/*!
 * Convenient macro to declare a static class.
 */
#define Q_STATIC_CLASS(Class) \
    Class() Q_DECL_EQ_DELETE; \
    Class(const Class&) Q_DECL_EQ_DELETE; \
    Class& operator=(const Class&) Q_DECL_EQ_DELETE; \
    virtual ~Class() Q_DECL_EQ_DELETE;

/*!
 * Convenient macro to declare a friend class.
 */
#define Q_FRIEND_CLASS(Class) friend class Class;

#endif // HBGLOBAL_H
