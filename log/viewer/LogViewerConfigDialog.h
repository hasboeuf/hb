#ifndef LOGVIEWERCONFIGDIALOG_H
#define LOGVIEWERCONFIGDIALOG_H

// Qt
#include <QButtonGroup>
// Local
#include <LogViewerConfig.h>
#include <ui_LogViewerConfigDialog.h>

namespace hb {
namespace logviewer {

class LogViewerConfigDialog : public QDialog, private Ui::LogViewerConfigDialog {
    Q_OBJECT
    Q_DISABLE_COPY(LogViewerConfigDialog)

public:
    LogViewerConfigDialog() = delete;
    LogViewerConfigDialog(LogViewerConfig& config, QWidget* parent = nullptr);
    virtual ~LogViewerConfigDialog() = default;

    const LogViewerConfig& config() const;

private:
    void updateGui();
    void saveConfig();
    void addEditorField(const QString& name, const QString& cmd);

    void onFontClicked();
    void onColorClicked(int color_id);
    void onBackgroundColorClicked();
    void onAddEditorClicked();
    void onSaveClicked();
    void onResetClicked();
    void onImportClicked();
    void onExportClicked();
    void onEditorNameChanged();

    LogViewerConfig mConfig;

    QButtonGroup qbg_colors;
    QList<QLineEdit*> qfl_editor_fields; // Use when saving.
};
} // namespace logviewer
} // namespace hb

#endif // LOGVIEWERCONFIGDIALOG_H
