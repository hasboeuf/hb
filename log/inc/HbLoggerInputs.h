/****************************************************************************
** Copyright (C) 2012-2015 Adrien Gavignet (hasboeuf)
** Contact: adrien.gavignet@gmail.com
**
** This file is part of the Hb module. Provided "AS IS", WITHOUT WARRANTIES
** OR CONDITIONS OF ANY KIND, either express or implied.
****************************************************************************/

#ifndef HBLOGGERINPUTS_H
#define HBLOGGERINPUTS_H

/*! \file HbLoggerInputs.h */

// Hb
#include <HbLog.h>
#include <HbLoggerStream.h>
#include <HbGlobal.h>

namespace hb
{
    namespace log
    {

        class IHbLoggerInput;
        class HbLoggerPool;

        /*!
         * HbLoggerInputs handles log inputs.
         * - Add a log input.
         * - Remove an existing input.
         */
        class HB_LOG_DECL HbLoggerInputs : public HbLoggerStream
        {
            Q_FRIEND_CLASS( HbLogManager )


        public:

            /*!
             * Request to add a tcp server input.
             * \param port Listening port.
             * \param error Error description in case of failure.
             * \return Input uid, 0 on failure.
             */
            loguid addTcpSocketInput( quint16 port, QString * error = nullptr );

            /*!
             * Request to add a local server input.
             * \param name Server name (defaulted on DEFAULT_LOCAL_SERVER_NAME).
             * \param error Error description in case of failure.
             * \return Input uid, 0 on failure.
             */
            loguid addLocalSocketInput( const QString & name = QString(), QString * error = nullptr );

            /*!
             * Request to delete an input.
             * \param uid Input uid to delete.
             * \param error Error description in case of failure.
             * \return True on success, false else.
             */
            bool removeInput( loguid uid, QString * error = nullptr );

            /*!
             * Get input informations.
             * \param uid Input uid.
             * \return Input on success, nullptr else.
             */
            IHbLoggerInput * input( loguid uid );

        private:

            HbLoggerInputs() = delete;
            HbLoggerInputs( HbLogManager * parent );
            virtual ~HbLoggerInputs() = default;

        private:

            HbLoggerPool * mpPool;
        };
    }
}

#endif // HBLOGGERINPUTS_H
