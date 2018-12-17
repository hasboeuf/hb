#ifndef LOGVIEWERCONFIG_H
#define LOGVIEWERCONFIG_H

// Qt
#include <QtCore/QMap>
#include <QtGui/QColor>
#include <QtGui/QFont>
// Hb
#include <gui/HbLogConfig.h>

namespace hb {
namespace logviewer {
using hb::log::HbLogConfig;

class LogViewerConfig : public HbLogConfig {
public:
    static const LogViewerConfig importConfigXml(const QString& file_path);
    static bool exportConfigXml(const QString& file_path, const LogViewerConfig& config);

    LogViewerConfig();
    LogViewerConfig(const LogViewerConfig& config);
    virtual ~LogViewerConfig() = default;

    LogViewerConfig& operator=(const LogViewerConfig& config);

    void addEditor(const QString& name, const QString& path);
    const QString editorCommand(const QString& editor_name) const;
    void resetEditors();
    QMap<QString, QString> editors() const;

    QString defaultEditor() const;
    void setDefaultEditor(const QString& editor);

    void resetProjectFolders();
    QStringList projectFolders() const;
    void addProjectFolder(const QString& folder);

    void loadSettings();
    void saveSettings();

protected:
    void buildDomFromConfig(QDomElement& root) const;
    void buildConfigFromDom(QDomElement& root);

private:
    QStringList mProjectFolders;
    QMap<QString, QString> mEditorCommands;
    QString mEditorDefault;
};
} // namespace logviewer
} // namespace hb

#endif // LOGVIEWERCONFIG_H
