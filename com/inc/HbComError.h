/****************************************************************************
** Copyright (C) 2012-2015 Adrien Gavignet (hasboeuf)
** Contact: adrien.gavignet@gmail.com
**
** This file is part of the Hb module. Provided "AS IS", WITHOUT WARRANTIES
** OR CONDITIONS OF ANY KIND, either express or implied.
****************************************************************************/

#ifndef HBCOMERROR_H
#define HBCOMERROR_H

// Qt
#include <QGlobal.h>
// Hb
#include <HbGlobal.h>
// Local
#include <HbCom.h>

namespace hb
{
    namespace com
    {

        class HB_COM_DECL HbComError
        {

        public:

            // TODO static
            enum Code
            {
                G_SUCCESS = 0,
                G_FAILLURE,
                G_ERROR_WTF,

                TCPSOCKETHANDLER_FULL,
                TCPSOCKETHANDLER_ALREADY_PRESENT,
                TCPSOCKETHANDLER_UNTHREADED_YET,
                TCPSOCKETHANDLER_BAD_DESCRIPTOR
            };
        };
    }
}


#endif // HBCOMERROR_H
