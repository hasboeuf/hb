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
        class HB_TOOLS_DECL HbSettings : public QObject
        {

        public:
            /**
             * HbSettings constructor.
             * \param parent Parent QObject.
             * \see init
             */
            HbSettings( QObject * parent = nullptr );

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

            /*!
             * Initialize QSettings format and scope.
             *
             * \param scope QSettings scope.
             * \param format QSettings format.
             * \see QSettings::setDefaultFormat
             */
            static void init( QSettings::Scope scope, QSettings::Format format );

        private:
            bool mIsValid;
            QSettings mSettings;

            static QSettings::Scope msScope;
            static QSettings::Format msFormat;
        };
    }
}

#endif // HBAPPLICATIONHELPER_H
