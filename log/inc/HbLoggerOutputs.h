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


        public :

            /*! 
            * Request the add of a console output.
            * To check the success of the operation, please store the id and connect the streamState signal.
            * \see streamState
            */
            loguid addConsoleOutput( QString * error = nullptr );

            /*! 
            * Request the add of a gui output.
            * To check the success of the operation, please store the id and connect the streamState signal.
            * \see streamState
            */
            loguid addGuiOutput( HbLogGuiNotifier * notifier, QString * error = nullptr );

            /*! 
            * Request the add of a file output.
            * To check the success of the operation, please store the id and connect the streamState signal.
            * \see streamState
            */
            loguid addFileOutput( const QString & file, quint32 max_size = 0, QString * error = nullptr );

            /*! 
            * Request the add of a tcp socket output.
            * To check the success of the operation, please store the id and connect the streamState signal.
            * \see streamState
            */
            loguid addTcpSocketOutput( const QString & ip, quint16 port, QString * error = nullptr );

            /*! 
            * Request the add of a local socket output.
            * To check the success of the operation, please store the id and connect the streamState signal.
            * \see streamState
            */
            loguid addLocalSocketOutput( const QString & name = QString(), QString * error = nullptr );

            /*! 
            * Request the deletion of an output specified by its id.
            * To check the success of the operation, please store the id and connect the streamState signal.
            * \see streamState
            */
            bool removeOutput( loguid uid, QString * error = nullptr );

            /*! 
            * Return the output specified by its id.
            */
            IHbLoggerOutput * output( loguid uid );

        private :

            HbLoggerOutputs() = delete;
            HbLoggerOutputs( HbLogManager * parent );
            virtual ~HbLoggerOutputs() = default;

        private :
            HbLoggerPool * mpPool;
        };


    }

}

#endif // HBLOGGEROUTPUTS_H
