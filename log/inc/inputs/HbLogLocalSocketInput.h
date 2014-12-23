#ifndef HBLOGLOCALSOCKETINPUT_H
#define HBLOGLOCALSOCKETINPUT_H

/*! \file HbLogLocalSocketInput.h */

// Qt
#include <QtNetwork/QLocalServer>
// Hb
#include <inputs/HbLogAbstractInput.h>
#include <HbGlobal.h>

namespace hb
{
	namespace log
	{
		/*! \namespace hb::log */

        class HbLogMessage;


        /*! 
        * \class HbLogLocalSocketInput
        * \brief The %HbLogLocalSocketInput class defines a local server input.
        *
        * %HbLogLocalSocketInput inherits from HbLogAbstractInput.\n
        */
        class HbLogLocalSocketInput final : public QLocalServer, public HbLogAbstractInput
		{
			Q_OBJECT
            Q_DISABLE_COPY( HbLogLocalSocketInput )

        private :

		public :

            HbLogLocalSocketInput(const QString & name = QString() );
            virtual ~HbLogLocalSocketInput() = default;

        signals :

            void inputMessageReceived( HbLogMessage * message );

		private callbacks :

			void incomingConnection();
			void onReadyRead();
			void onClientDisconnected();


        private :
			QString mName;
            qint32 mAvailable;
            QSet< QLocalSocket * > mClients;
		};
	}
}

#endif

