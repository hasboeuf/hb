/****************************************************************************
** Copyright (C) 2012-2015 Adrien Gavignet (hasboeuf)
** Contact: adrien.gavignet@gmail.com
**
** This file is part of the Hb module. Provided "AS IS", WITHOUT WARRANTIES
** OR CONDITIONS OF ANY KIND, either express or implied.
****************************************************************************/

#ifndef HBENUM_H
#define HBENUM_H

/*! \file HbEnum.h */

// Hb
#include <HbTools.h>
#include <HbEnumerator.h>

namespace HbPrivate
{
    /*!
    * \class HbEnumHelper
    * \brief The %HbEnumHelper template class provides meta-data about an enumerator.
    *
    * %HbEnumHelper implements a meta-enumeration system, which allows to discover information about and manipulate values of any \a Enum enumerator declared in \a Class.
    * To activate it :
    *   \li Qt meta object system's support have to be enabled for \a Class
    *   \li Enumerators have to be registered into the Qt meta-enumeration system
    *   \li #Q_ENUMS_HANDLER macro must be declared inside the private section of \a Class to enable meta-enumeration features
    *
    * \see Qt Meta-Object System
    */
    template< typename Class, typename Enum >
    class HbEnumHelper
    {
        Q_DEFAULT_COPY( HbEnumHelper )


    public :

        /*!
        * Returns the name of the enumerator (without the scope).
        */
        static QString name()
        {
            return HbPrivate::HbEnumerator< Class >::template name< Enum >();
        }

        /*!
        * Returns the number of values defined in the enumerator.
        */
        static qint16 count()
        {
            return HbPrivate::HbEnumerator< Class >::template count< Enum >();
        }

        /*!
        * Returns true if this enumerator is used as a flag; otherwise returns false.\n
        * When used as flags, enumerator can be combined using the OR operator.
        */
        static bool isFlag()
        {
            return HbPrivate::HbEnumerator< Class >::template isFlag< Enum >();
        }

        /*!
        * Returns the enumerator value of the given \a index, or invalid value if no such key exists.
        */
        static nullable< Enum > value( qint16 index )
        {
            return HbPrivate::HbEnumerator< Class >::template value< Enum >( index );
        }

        /*!
        * Returns index of the given enumerator \a value, or -1 if value is not defined.
        */
        static qint16 index( Enum value )
        {
            return HbPrivate::HbEnumerator< Class >::index( value );
        }

        /*!
        * Returns the label of the given enumerator \a value, or an empty string if value is not defined.
        */
        static QString toString( Enum value )
        {
            return HbPrivate::HbEnumerator< Class >::toString( value );
        }

        /*!
        * Returns all labels contains in the given enumerator \a value, or an empty list if enumerator is empty.
        */
        static QStringList toString()
        {
            return HbPrivate::HbEnumerator< Class >::template toString< Enum >();
        }

        /*!
        * Returns the enumerator value of the given \a label, or invalid value if no such label exists.
        */
        static nullable< Enum > fromString( const QString & label )
        {
            return HbPrivate::HbEnumerator< Class >::template fromString< Enum >( label );
        }

        /*!
        * Returns the enumerator value of the given \a label, or \a defaultValue value if no such label exists.
        */
        static Enum fromString( const QString & label, Enum defaultValue )
        {
            return HbPrivate::HbEnumerator< Class >::template fromString< Enum >( label ).value( defaultValue );
        }
    };
}


/*!
* \def Q_ENUMS_HANDLER( Class )
* \hideinitializer
* The %Q_ENUMS_HANDLER macro must appear in the private section of a \a Class definition, 
* in order to make meta-enumeration features available for any enumerator declared in \a Class.
*/
#define Q_ENUMS_HANDLER( Class ) \
public : \
\
    template< typename Enum > \
	class HbEnum : public HbPrivate::HbEnumHelper< Class, Enum > {}; \
\
private :

/*!
* \def Q_META_ENUMS( Enum )
* \hideinitializer
* This macro defines a \a Meta(Enum) class which provides meta-data access for \a Enum type registered.
*
* For example :
  \code{.h}
    #include <HbEnum.h>

    class MyClass : public QObject
    {
        Q_OBJECT
        Q_ENUMS_HANDLER(MyClass)  

        Q_ENUMS(Priority)

    public :

        enum Priority { Low, Normal, High };
        Q_META_ENUMS(Priority)  // provides MetaPriority type

    public :

        MyClass(QObject * parent = nullptr);
        ~MyClass();
    };        
  \endcode
* <b></b>
  \code{.cpp}
    #include <MyClass.h>

    static QString printEnum( MyClass::Priority value )
    {
        return MyClass::MetaPriority::toString( value );
    }
  \endcode
*
* \warning enum type must be declared before calling this macro.
*/
#define Q_META_ENUMS( Enum ) \
    typedef HbEnum< Enum > Meta ## Enum;


#endif
