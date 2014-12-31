/****************************************************************************
** Copyright (C) 2012-2015 Adrien Gavignet (hasboeuf)
** Contact: adrien.gavignet@gmail.com
**
** This file is part of the Hb module. Provided "AS IS", WITHOUT WARRANTIES
** OR CONDITIONS OF ANY KIND, either express or implied.
****************************************************************************/

#ifndef HBSINGLETON_H
#define HBSINGLETON_H

// System
#include <iostream>

namespace hb
{
    namespace tools
    {

        template <class T>
        class HbSingleton
        {

        public:
            static T* get()
            {
                if(mInstance == 0)
                {
                    mInstance = new T();
                }
                return mInstance;
            }

            static void kill()
            {
                if(mInstance)
                {
                    delete mInstance;
                    mInstance = 0;
                }
            }

        protected:
            static T* mInstance;

        private:
            T& operator=(const T&);
        };
    }
}

using hb::tools::HbSingleton;

template<typename T>
T* HbSingleton<T>::mInstance = 0;

#endif // HBSINGLETON_H
