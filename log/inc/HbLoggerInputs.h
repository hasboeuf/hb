/****************************************************************************
** Copyright (C) 2012-2015 Adrien Gavignet (hasboeuf)
** Contact: adrien.gavignet@gmail.com
**
** This file is part of the Hb module. Provided "AS IS", WITHOUT WARRANTIES
** OR CONDITIONS OF ANY KIND, either express or implied.
****************************************************************************/

#ifndef HBLOGGERINPUTS_H
#define HBLOGGERINPUTS_H

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


        class HB_LOG_DECL HbLoggerInputs : public HbLoggerStream
        {
            Q_FRIEND_CLASS( HbLogManager )


        public :

            /*! 
            * Request the add of a tcp server input.
            * To check the success of the operation, please store the id and connect the streamState signal.
            * \see streamState
            */
            loguid addTcpSocketInput( quint16 port, QString * error = nullptr );

            /*! 
            * Request the add of a local server input.
            * To check the success of the operation, please store the id and connect the streamState signal.
            * \see streamState
            */
            loguid addLocalSocketInput( const QString & name = QString(), QString * error = nullptr );

            /*! 
            * Request the deletion of an input specified by its id.
            * To check the success of the operation, please store the id and connect the streamState signal.
            * \see streamState
            */
            bool removeInput(loguid uid, QString * error = nullptr );

            /*! 
            * Return the output specified by its id.
            */
            IHbLoggerInput * input( loguid id );

        private :

            HbLoggerInputs() = delete;
            HbLoggerInputs( HbLogManager * parent );
            virtual ~HbLoggerInputs() = default;


        private :

            HbLoggerPool * mpPool;
        };
    }
}

#endif // HBLOGGERINPUTS_H
