#ifndef LOGVIEWER_H
#define LOGVIEWER_H

// Qt
#include <QtCore/QMutex>
#include <QtCore/QTimer>
// Local
#include <ui_LogViewer.h>
#include <LogViewerConfig.h>

namespace hb
{
    namespace log
    {
        class HbLogGuiNotifier;
        class HbLogMessage;
    }

    namespace logviewer
    {
        class LogViewerTab;

        using hb::log::HbLogGuiNotifier;
        using hb::log::HbLogMessage;

        
        class LogViewer final : public QWidget, private Ui::LogViewer
        {
            Q_OBJECT
            Q_DISABLE_COPY( LogViewer )


        public :

            LogViewer( QWidget *parent = nullptr );
            virtual ~LogViewer() = default;

            void loadConfigPath( const QString & path );
            void loadConfigSettings();

            HbLogGuiNotifier * logNotifier() const;

        private slots :

            // From mLogNotifier.
            void onNewLogMessage( const HbLogMessage & message );

            // From GUI.
            void onOpenFileClicked   ();
            void onConfigureClicked  ();
            void onRefreshTimeChanged( int refresh );
            void onTabCloseRequested ( int index );

            // From mProcessTimer.
            void processLogMessage();

            // From LogViewerTab.
            void onNewTabRequest( quint8 column, const QString & value );


        private :

            quint32 mTabIds;
            QHash<quint32, LogViewerTab *> mTabs;

            HbLogGuiNotifier * mpLogNotifier;

            LogViewerConfig mConfig;

            QTimer mProcessTimer;
            QMutex mMutexBuffer;
            QList< HbLogMessage * > mTempBuffer;
        };
    }
}

#endif
