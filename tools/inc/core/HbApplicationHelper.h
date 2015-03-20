/****************************************************************************
** Copyright (C) 2012-2015 Adrien Gavignet (hasboeuf)
** Contact: adrien.gavignet@gmail.com
**
** This file is part of the Hb module. Provided "AS IS", WITHOUT WARRANTIES
** OR CONDITIONS OF ANY KIND, either express or implied.
****************************************************************************/

#ifndef HBAPPLICATIONHELPER_H
#define HBAPPLICATIONHELPER_H

/*! \file HbApplicationHelper.h */

// Local
#include <HbTools.h>

namespace hb
{
    namespace tools
    {
        /*!
         * TODOC
         * HbApplicationHelper provides helper methods for the application.
         */
        class HB_TOOLS_DECL HbApplicationHelper
        {

        public:
            /*!
             * Initialize app.
             * Initialize QSetting.
             * Generate seed for qsrand.
             * Call it in main().
             * \param company Company name e.g.: MyCompany
             * \param domain Domain name e.g.: mycompany.io
             * \param name Application name e.g.: MyApp, by default it is the executable name.
             */
            static void initApp(const QString & company, const QString & domain, const QString & name = QString());

            /*!
             * Set the skin of the app, colors used are personal taste.
             * Call it in main().
             * \param skin Name of the style used in QStyleFactory.
             */
            static void initSkin(const QString & skin);
        };
    }
}

#endif // HBAPPLICATIONHELPER_H
