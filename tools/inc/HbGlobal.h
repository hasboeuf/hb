/****************************************************************************
** Copyright (C) 2012-2015 Adrien Gavignet (hasboeuf)
** Contact: adrien.gavignet@gmail.com
**
** This file is part of the Hb module. Provided "AS IS", WITHOUT WARRANTIES
** OR CONDITIONS OF ANY KIND, either express or implied.
****************************************************************************/

#ifndef HBGLOBAL_H
#define HBGLOBAL_H

//! \file HbGlobal.h

// Qt
#include <QtCore/QString>


#if defined( Q_OS_WIN32 )
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



#if defined( Q_OS_ANDROID )
#   define Q_OS_MOBILE
#endif



#if defined( Q_CC_GNU ) || defined( Q_CC_MINGW )
#    include <cxxabi.h>
#    include <typeinfo>
#endif



#if !defined( Q_EXTERN_C )
#   ifdef __cplusplus
#       define Q_EXTERN_C extern "C"
#   else
#       define Q_EXTERN_C extern
#   endif
#endif



#if !defined( QT_NO_DEBUG )
#   define q_assert( test ) ( ( test ) ? qt_noop() : qt_assert( #test, __FILE__, __LINE__ ) )
#else
#   define q_assert( test ) ( ( test ) ? qt_noop() : qt_noop() )
#endif



#if !defined( QT_NO_DEBUG )
#   define q_assert_x( test, where, what ) ( ( test ) ? qt_noop() : qt_assert_x( where, what, __FILE__, __LINE__ ) )
#else
#   define q_assert_x( test, where, what ) ( ( test ) ? qt_noop() : qt_noop() )
#endif



#if !defined( HbLatin1 )
#   define HbLatin1( string ) QString( string ).toLatin1().constData()
#endif


namespace HbPrivate // TODO anonymous
{

    inline QString hb_scopename(const char * type)
    {
#if defined( Q_CC_MSVC )
        QString name;
        name = QLatin1String(type);
#elif defined( Q_CC_GNU ) || defined( Q_CC_MINGW )
        QString name;
        qint32 status = 0;

        char * demangled = abi::__cxa_demangle(
            type, nullptr, nullptr, &status);

        Q_ASSERT(status == 0);

        name = QLatin1String(demangled);
        free(demangled);
#endif
        return name;
    }

    inline QString hb_typename( const char * type )
    {
        QString name(hb_scopename(type));

        if ( !name.isEmpty() )
        {
            qint32 truncate = 0;

            if ( ( truncate = name.lastIndexOf( QLatin1String( " *" ) ) ) > 0 )
                name.truncate(truncate);

            if ( ( truncate = name.lastIndexOf( QChar::Space ) ) > 0 )
                name = name.right( name.length() - ( truncate + 1 ) );

            if ( ( truncate = name.lastIndexOf(QLatin1Char( ':' ) ) ) > 0 )
                name = name.right( name.length() - ( truncate + 1 ) );
        }

        return name;
    }
}



template< typename T >
inline QString qScopeName()
{
    return HbPrivate::hb_scopename(typeid(T).name());
}




template< typename T >
inline QString qScopeName(T * pointer)
{
    return (pointer) ? HbPrivate::hb_scopename(typeid(*pointer).name()) : QString();
}




template< typename T >
inline QString qScopeName(const T & expression)
{
    return HbPrivate::hb_scopename(typeid(expression).name());
}




template< typename T >
inline QString qTypeName()
{
    return HbPrivate::hb_typename(typeid(T).name());
}




template< typename T >
inline QString qTypeName(T * pointer)
{
    return (pointer) ? HbPrivate::hb_typename(typeid(*pointer).name()) : QString();
}




template< typename T >
inline QString qTypeName(const T & expression)
{
    return HbPrivate::hb_typename(typeid(expression).name());
}




namespace HbPrivate // TODO anonymous
{

    template< typename T >
    inline T * hb_assert_ptr( T * pointer, const char * file, qint32 line )
    {
#if !defined( QT_NO_DEBUG )
        if ( !pointer )
            qFatal( "Null %s pointer detected in file %s, line %d",
            HbLatin1( qScopeName< T >() ), file, line );
#else
        Q_UNUSED( file );
        Q_UNUSED( line );
#endif
        return pointer;
    }


    template< typename U, typename T >
    inline U hb_dynamic_cast( T * pointer, const char * file, qint32 line )
    {
#if !defined( QT_NO_DEBUG )

        U ptr_cast = dynamic_cast< U >(pointer);

        if ( pointer && !ptr_cast )
        {
            qFatal("Invalid %s pointer cast detected in file %s, line %d",
                HbLatin1( qScopeName< U >() ), file, line );
        }

        return ptr_cast;

#else
        Q_UNUSED( file );
        Q_UNUSED( line );

        return dynamic_cast< U >( pointer );
#endif
    }

}



#define q_assert_ptr( pointer ) HbPrivate::hb_assert_ptr( pointer, __FILE__, __LINE__ )



#define q_dynamic_cast( Type, pointer ) HbPrivate::hb_dynamic_cast< Type >( pointer, __FILE__, __LINE__ )




template< typename U, typename T >
inline QList< U > qlist_dynamic_cast( const QList< T * > & list )
{
    QList< U > list_cast;

    foreach( T * item, list )
        list_cast.append( q_dynamic_cast( U, item ) );

    return list_cast;
}

template< typename T >
inline void q_delete_ptr( T ** pointer )
{
    delete *pointer;
    *pointer = nullptr;
}


inline void qExit()
{
    exit(EXIT_SUCCESS);
}


inline void qAbort()
{
    exit(EXIT_FAILURE);
}


#define callbacks


#define inner


#define Q_DEFAULT_COPY( Class ) \
    public: \
    Class(const Class &) Q_DECL_EQ_DEFAULT; \
    Class & operator =(const Class &)Q_DECL_EQ_DEFAULT; \
    private:



#define Q_STATIC_CLASS( Class ) \
    Class() Q_DECL_EQ_DELETE; \
    Class(const Class &) Q_DECL_EQ_DELETE; \
    Class & operator =(const Class &)Q_DECL_EQ_DELETE; \
    virtual ~Class() Q_DECL_EQ_DELETE;



#define Q_FRIEND_CLASS( Class ) \
    friend class Class;


#endif // HBGLOBAL_H
