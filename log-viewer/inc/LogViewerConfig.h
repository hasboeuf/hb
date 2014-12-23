#ifndef LOGVIEWERCONFIG_H
#define LOGVIEWERCONFIG_H

// Qt
#include <QtGui/QColor>
#include <QtGui/QFont>
#include <QtCore/QMap>
// Hb
#include <gui/HbLogConfig.h>

namespace hb
{
    namespace logviewer
	{

        class LogViewerConfig final : public hb::log::HbLogConfig
        {
            Q_OBJECT

        public :
			static const LogViewerConfig importConfigXml(QString file_path);
			static bool exportConfigXml(QString file_path, const LogViewerConfig & config);

            LogViewerConfig();
            LogViewerConfig( const LogViewerConfig & config );
            virtual ~LogViewerConfig() = default;

            LogViewerConfig & operator =( const LogViewerConfig & config );

			void addEditor(QString name, QString path);
			QString editorCommand(QString editor_name) const;
			void resetEditors();
			QMap< QString, QString > editors() const;

			QString defaultEditor() const;
			void setDefaultEditor(QString editor);

			void resetProjectFolders();
			QStringList projectFolders() const;
			void addProjectFolder(QString folder);

            void loadSettings();
            void saveSettings();

		protected:
			void buildDomFromConfig(QDomElement& root) const;
			void buildConfigFromDom(QDomElement& root);

        private :
            QStringList mProjectFolders;
            QMap< QString, QString > mEditorCommands;
            QString mEditorDefault;
        };
    }
}

#endif // LOGVIEWERCONFIG_H
