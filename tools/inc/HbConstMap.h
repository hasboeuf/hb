/****************************************************************************
** Copyright (C) 2012-2015 Adrien Gavignet (hasboeuf)
** Contact: adrien.gavignet@gmail.com
**
** This file is part of the Hb module. Provided "AS IS", WITHOUT WARRANTIES
** OR CONDITIONS OF ANY KIND, either express or implied.
****************************************************************************/

#ifndef HBCONSTMAP_H
#define HBCONSTMAP_H

// Qt
#include <QtCore/QMap>

template<typename K, typename V> struct     Map :
    public                                  QMap<K,V>
{
    typedef Map<K,V>                        Base;
    Map<K,V>&                               add( K k, V v );
    const V                                 get( K k) const;
};

template<typename K, typename V> inline Map<K,V>& Map<K,V>::add( K k, V v )
{
    (*this)[k] = v;
    return( *this );
}

template<typename K, typename V> inline const V Map<K,V>::get( K k) const
{
    return (*this)[k];
}

#endif // HBCONSTMAP_H
