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
