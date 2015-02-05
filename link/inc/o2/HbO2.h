/****************************************************************************
** Copyright (C) 2012-2015 Adrien Gavignet (hasboeuf)
** Contact: adrien.gavignet@gmail.com
**
** This file is part of the Hb module. Provided "AS IS", WITHOUT WARRANTIES
** OR CONDITIONS OF ANY KIND, either express or implied.
****************************************************************************/

#ifndef HBO2_H
#define HBO2_H

// Qt
#include <QtCore/QObject>
// Local
#include <HbLink.h>


namespace hb
{
    namespace link
    {
        class HB_LINK_DECL HbO2 : public QObject
        {
            Q_OBJECT

        public:
            HbO2() = default;
            virtual ~HbO2() = default;
        };
    }
}

#endif // HBO2_H
