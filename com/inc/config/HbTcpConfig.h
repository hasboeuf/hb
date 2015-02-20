/****************************************************************************
** Copyright (C) 2012-2015 Adrien Gavignet (hasboeuf)
** Contact: adrien.gavignet@gmail.com
**
** This file is part of the Hb module. Provided "AS IS", WITHOUT WARRANTIES
** OR CONDITIONS OF ANY KIND, either express or implied.
****************************************************************************/

#ifndef HBTCPCONFIG_H
#define HBTCPCONFIG_H

// Qt
#include <QtNetwork/QHostAddress>
// Local
#include <config/HbComConfig.h>


namespace hb
{
    namespace com
    {

        class HB_COM_DECL HbTcpConfig : public virtual HbComConfig
        {
        public:

            enum class SocketOption : qint16
            {
                NoOptions = 0,
                LowDelay = 1 << 0,
                KeepAlive = 1 << 1,
                MulticastLoopback = 1 << 2
            };
            Q_DECLARE_FLAGS( SocketOptions, SocketOption )

            HbTcpConfig();
            virtual ~HbTcpConfig() = default;
            HbTcpConfig(const HbTcpConfig & config);
            HbTcpConfig & operator =(const HbTcpConfig & config);

            bool isValid() const;

            void setAddress(const QString & address);
            void setAddress(const QHostAddress & address);
            void setPort   (quint16 port);
            void setOptions(SocketOptions options);

            const QHostAddress & address() const;
            quint16 port() const;
            SocketOptions options() const;

        private:
            QHostAddress  mAddress;
            quint16       mPort;
            SocketOptions mOptions;
        };

    }
}

using hb::com::HbTcpConfig;

#endif // HBTCPCONFIG_H
