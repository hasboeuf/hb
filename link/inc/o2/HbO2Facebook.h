/****************************************************************************
** Copyright (C) 2012-2015 Adrien Gavignet (hasboeuf)
** Contact: adrien.gavignet@gmail.com
**
** This file is part of the Hb module. Provided "AS IS", WITHOUT WARRANTIES
** OR CONDITIONS OF ANY KIND, either express or implied.
****************************************************************************/

#ifndef HBO2FACEBOOK_H
#define HBO2FACEBOOK_H

// Qt
#include <QtCore/QObject>
// Local
#include <HbLink.h>
#include <o2/HbO2.h>


namespace hb
{
    namespace link
    {
        class HB_LINK_DECL HbO2Facebook : public HbO2
        {
            Q_OBJECT

        public:
            HbO2Facebook() = default;
            virtual ~HbO2Facebook() = default;
        };
    }
}

using hb::link::HbO2Facebook;

#endif // HBO2FACEBOOK_H
