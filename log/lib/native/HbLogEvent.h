#ifndef HBLOGEVENT_H
#define HBLOGEVENT_H

// Qt
#include <QtCore/QMetaType>
#include <QtCore/QString>

namespace hb {
    namespace log {


        class HbLogEvent final
        {
        public :

            HbLogEvent();
            HbLogEvent( const HbLogEvent & event );
            HbLogEvent( QtMsgType level, const QString & message );
            HbLogEvent( QtMsgType level, const char * file, qint32 line, const char * function, const QString & message );
            virtual ~HbLogEvent();

            HbLogEvent & operator =( const HbLogEvent & event );

            const char * file() const;
            qint32 line() const;
            const char * function() const;

            QtMsgType level() const;
            const QString & message() const;


        private :

            const char * _file;
            qint32 _line;
            const char * _function;

            QtMsgType _level;
            QString _message;
        };
    }
}

Q_DECLARE_METATYPE( hb::log::HbLogEvent );

#endif // HBLOGEVENT_H
