#ifndef LOGVIEWERCONFIGDIALOG_H
#define LOGVIEWERCONFIGDIALOG_H

// Local
#include <ui_LogViewerConfigDialog.h>
#include <LogViewerConfig.h>

namespace hb
{
    namespace logviewer
	{

		class LogViewerConfigDialog final : public QDialog, private Ui::LogViewerConfigDialog
        {
            Q_OBJECT
            Q_DISABLE_COPY( LogViewerConfigDialog )


        public :

            LogViewerConfigDialog() = delete;
            LogViewerConfigDialog( LogViewerConfig & config, QWidget * parent = nullptr );
            virtual ~LogViewerConfigDialog() = default;

            const LogViewerConfig & config() const;

        private :
            void updateGui     ();
            void saveConfig    ();
            void addEditorField( const QString & name, const QString & cmd );

        private slots :
            void onFontClicked           ();
            void onColorClicked          ( int color_id );
            void onBackgroundColorClicked();
            void onAddEditorClicked      ();
            void onSaveClicked           ();
            void onResetClicked          ();
            void onImportClicked         ();
            void onExportClicked         ();
            void onEditorNameChanged     ();

        private :

            LogViewerConfig mConfig;

            QButtonGroup qbg_colors;
            QList< QLineEdit * > qfl_editor_fields; // Use when saving.
        };
    }
}

#endif // LOGVIEWERCONFIGDIALOG_H
