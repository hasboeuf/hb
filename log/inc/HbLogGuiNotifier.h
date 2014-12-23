#ifndef HBLOGGUINOTIFIER_H
#define HBLOGGUINOTIFIER_H

// Qt
#include <QtCore/QObject>
// Hb
#include <HbLog.h>

namespace hb
{
	namespace log
	{

        class HbLogMessage;


        class HB_LOG_DECL HbLogGuiNotifier final : public QObject
		{
			Q_OBJECT
            Q_DISABLE_COPY( HbLogGuiNotifier )


        public :

            HbLogGuiNotifier();
            virtual ~HbLogGuiNotifier() = default;

        signals :

            void newLogMessage( const HbLogMessage & message );

		private :

            Q_INVOKABLE void onNewLogMessage( const HbLogMessage & message );
		};
	}
}

#endif // HBLOGGUINOTIFIER_H
