/****************************************************************************
** Copyright (C) 2012-2015 Adrien Gavignet (hasboeuf)
** Contact: adrien.gavignet@gmail.com
**
** This file is part of the Hb module. Provided "AS IS", WITHOUT WARRANTIES
** OR CONDITIONS OF ANY KIND, either express or implied.
****************************************************************************/

#ifndef HBLOGGEROUTPUTS_H
#define HBLOGGEROUTPUTS_H

/*! \file HbLoggerOutputs.h */

#include <HbLoggerStream.h>

#include <HbLog.h>
#include <HbGlobal.h>

namespace hb
{
    namespace log
    {

        class IHbLoggerOutput;
        class HbLogGuiNotifier;
        class HbLoggerPool;

        /*!
         * TODOC.
         */
        class HB_LOG_DECL HbLoggerOutputs : public HbLoggerStream
        {
            Q_FRIEND_CLASS( HbLogManager )


        public:

            /*!
             * Request to add a console output.
             * Only one console per application is allowed.
             * \param error Error description in case of failure.
             * \return Output uid, 0 on failure.
             */
            loguid addConsoleOutput( QString * error = nullptr );

            /*!
             * Request to add a gui output.
             * \param notifier Gui notifier to connect.
             * \param error Error description in case of failure.
             * \return Output uid, 0 on failure.
             */
            loguid addGuiOutput( HbLogGuiNotifier * notifier, QString * error = nullptr );

            /*!
             * Request to add a file output.
             * \param dir Directory to put log files (according to QDir path).
             * \param max_size Max size of log file in Mo (if 0, msMaxFileSize (=100 Mo) will be used).
             * \param error Error description in case of failure.
             * \return Output uid, 0 on failure.
             */
            loguid addFileOutput( const QString & dir, quint32 max_size = 0, QString * error = nullptr );

            /*!
             * Request to add a tcp socket output.
             * \param ip Ip of the log server.
             * \param port Server port to connect.
             * \param error Error description in case of failure.
             * \return Output uid, 0 on failure.
             */
            loguid addTcpSocketOutput( const QString & ip, quint16 port, QString * error = nullptr );

            /*!
             * Request to add a local socket output.
             * \param name Server name (defaulted on DEFAULT_LOCAL_SERVER_NAME).
             * \param error Error description in case of failure.
             * \return Output uid, 0 on failure.
             */
            loguid addLocalSocketOutput( const QString & name = QString(), QString * error = nullptr );

            /*!
             * Request to delete an output.
             * \param uid Output uid to delete.
             * \param error Error description in case of failure.
             * \return True on success, false else.
             */
            bool removeOutput( loguid uid, QString * error = nullptr );

            /*!
             * Get output informations.
             * \param uid Output uid.
             * \return Output on success, nullptr else.
             */
            IHbLoggerOutput * output( loguid uid );

        private:

            HbLoggerOutputs() = delete;
            HbLoggerOutputs( HbLogManager * parent );
            virtual ~HbLoggerOutputs() = default;

        private:
            HbLoggerPool * mpPool;
        };


    }

}

#endif // HBLOGGEROUTPUTS_H
