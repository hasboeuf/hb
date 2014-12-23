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
