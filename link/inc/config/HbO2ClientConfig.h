/****************************************************************************
** Copyright (C) 2012-2015 Adrien Gavignet (hasboeuf)
** Contact: adrien.gavignet@gmail.com
**
** This file is part of the Hb module. Provided "AS IS", WITHOUT WARRANTIES
** OR CONDITIONS OF ANY KIND, either express or implied.
****************************************************************************/

#ifndef HBO2CLIENTCONFIG_H
#define HBO2CLIENTCONFIG_H

/*! \file HbO2ClientConfig.h */

// Qt
// Hb
#include <QtCore/QStringList>
// Local
#include <config/HbO2Config.h>

namespace hb
{
    namespace link
    {

        /*!
         * TODOC
         */
        class HB_LINK_DECL HbO2ClientConfig final : public HbO2Config
        {

        public:
            HbO2ClientConfig();
            HbO2ClientConfig( const HbO2ClientConfig & config );
            virtual ~HbO2ClientConfig() = default;
            virtual HbO2ClientConfig & operator =( const HbO2ClientConfig & config );

            virtual bool isValid() const;

            virtual bool read( QDataStream & stream );
            virtual bool write( QDataStream & stream ) const;

            virtual void setLocalPort( quint16 local_port ) final;
            virtual quint16 localPort() const final;

            virtual void addScope( const QString & permission  ) final;
            virtual void setScopes( const QStringList & permissions ) final;
            virtual const QStringList & scopes() const final;
            virtual const QString scopesStr() const final;

            virtual void setScopeSeparator( const QString & separator ) final;

        private:
            QStringList mScopes;
            QString     mScopesSeparator;
            quint16 mLocalPort;
        };
    }
}

using hb::link::HbO2ClientConfig;

#endif // HBO2CLIENTCONFIG_H
