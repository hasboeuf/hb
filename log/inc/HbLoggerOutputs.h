#ifndef HBLOGGEROUTPUTS_H
#define HBLOGGEROUTPUTS_H

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


        class HB_LOG_DECL HbLoggerOutputs : public HbLoggerStream
		{
            Q_FRIEND_CLASS( HbLogManager )


		public :

            /*! 
            * Request the add of a console output.
			* To check the success of the operation, please store the id and connect the streamState signal.
			* \see streamState
            */
			bool addConsoleOutput( quint32 id );

            /*! 
            * Request the add of a gui output.
			* To check the success of the operation, please store the id and connect the streamState signal.
			* \see streamState
            */
            bool addGuiOutput( quint32 id, HbLogGuiNotifier * notifier );

            /*! 
            * Request the add of a file output.
			* To check the success of the operation, please store the id and connect the streamState signal.
			* \see streamState
            */
			bool addFileOutput(quint32 id, const QString & file, quint32 max_size = 0);

            /*! 
            * Request the add of a tcp socket output.
			* To check the success of the operation, please store the id and connect the streamState signal.
			* \see streamState
            */
			bool addTcpSocketOutput( quint32 id, const QString & ip, quint32 port );

            /*! 
            * Request the add of a local socket output.
			* To check the success of the operation, please store the id and connect the streamState signal.
			* \see streamState
            */
			bool addLocalSocketOutput( quint32 id, const QString & name = QString() );

            /*! 
            * Request the deletion of an output specified by its id.
			* To check the success of the operation, please store the id and connect the streamState signal.
			* \see streamState
            */
			bool removeOutput( quint32 id );

            /*! 
            * Return the output specified by its id.
            */
            IHbLoggerOutput * output( quint32 id );

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
