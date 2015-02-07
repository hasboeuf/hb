/****************************************************************************
** Copyright (C) 2012-2015 Adrien Gavignet (hasboeuf)
** Contact: adrien.gavignet@gmail.com
**
** This file is part of the Hb module. Provided "AS IS", WITHOUT WARRANTIES
** OR CONDITIONS OF ANY KIND, either express or implied.
****************************************************************************/

#ifndef HBO2SERVERFACEBOOK_H
#define HBO2SERVERFACEBOOK_H

// Qt
// Local
#include <HbLink.h>
#include <server/HbO2Server.h>


namespace hb
{
    namespace link
    {
        class HB_LINK_DECL HbO2ServerFacebook : public HbO2Server
        {
            Q_OBJECT

        public:

            HbO2ServerFacebook() = default;
            virtual ~HbO2ServerFacebook() = default;

        protected:
            virtual const QUrl endPoint() const;
            virtual const QHash< QString, QString > tokenRequest() const;
            virtual LinkStatus tokenResponse( const QHash< QString, QString > & response );

        };
    }
}

using hb::link::HbO2ServerFacebook;

#endif // HBO2SERVERFACEBOOK_H
