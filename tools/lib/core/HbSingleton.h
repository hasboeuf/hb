/****************************************************************************
** Copyright (C) 2012-2015 Adrien Gavignet (hasboeuf)
** Contact: adrien.gavignet@gmail.com
**
** This file is part of the Hb module. Provided "AS IS", WITHOUT WARRANTIES
** OR CONDITIONS OF ANY KIND, either express or implied.
****************************************************************************/

#ifndef HBSINGLETON_H
#define HBSINGLETON_H

/*! \file HbSingleton.h */

// System
#include <iostream>

namespace hb {
namespace tools {

/*!
 * HbSingleton represents a non-threadsafe singleton class.
 */
template <class T> class HbSingleton {
public:
    static T* get() {
        if (mInstance == nullptr) {
            mInstance = new T();
        }
        return mInstance;
    }

    static void kill() {
        if (mInstance) {
            delete mInstance;
            mInstance = nullptr;
        }
    }

protected:
    static T* mInstance;

private:
    T& operator=(const T&);
};
} // namespace tools
} // namespace hb

using hb::tools::HbSingleton;

template <typename T> T* HbSingleton<T>::mInstance = nullptr;

#endif // HBSINGLETON_H
