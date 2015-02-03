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

        template < class T >
        class HbSingleton
        {

        public:
            static T * get()
            {
                if( mpInstance == nullptr )
                {
                    mpInstance = new T();
                }
                return mpInstance;
            }

            static void kill()
            {
                if( mpInstance )
                {
                    delete mpInstance;
                    mpInstance = nullptr;
                }
            }

        protected:
            static T * mpInstance;

        private:
            T & operator=( const T & );
        };
    }
}

using hb::tools::HbSingleton;

template< typename T >
T * HbSingleton< T >::mpInstance = nullptr;

#endif // HBSINGLETON_H
