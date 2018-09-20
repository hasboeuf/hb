/****************************************************************************
** Copyright (C) 2012-2015 Adrien Gavignet (hasboeuf)
** Contact: adrien.gavignet@gmail.com
**
** This file is part of the Hb module. Provided "AS IS", WITHOUT WARRANTIES
** OR CONDITIONS OF ANY KIND, either express or implied.
****************************************************************************/

#ifndef HBSETTINGS_H
#define HBSETTINGS_H

// Qt
#include <QtCore/QObject>
#include <QtCore/QSettings>
// Local
#include <HbTools.h>

namespace hb
{
    namespace tools
    {
        /*!
         * HbSettings provides settings conveniencies.
         */
        class HB_TOOLS_DECL HbSettings
        {
        public:
            /**
             * HbSettings constructor.
             * \param parent Parent QObject.
             */
            HbSettings();

            /**
             * HbSettings constructor.
             * \param scope QSettings scope.
             * \param format QSettings format.
             */
            HbSettings( QSettings::Format format, QSettings::Scope scope );

            /**
             * Write data in application settings.
             * \param key Data index.
             * \param data Data.
             * \return true if succeeds, false otherwise.
             */
            bool write( const QString key, const QVariant & data );

            /**
             * Get data from application settings.
             * \param key Data index.
             * \return Valid or invalid QVariant.
             */
            QVariant read( const QString & key );

            /**
             * Clear data from application settings.
             * \param key Data index to clear.
             */
            void remove( const QString & key );

            bool isValid() const;

        private:
            QSettings mSettings;
        };
    }
}

#endif // HBAPPLICATIONHELPER_H
