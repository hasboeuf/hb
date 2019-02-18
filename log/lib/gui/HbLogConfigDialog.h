#ifndef HBLOGCONFIGDIALOG_H
#define HBLOGCONFIGDIALOG_H

/*! \file HbLogConfigDialog.h */

// Qt
#include <QButtonGroup>
// Local
#include <HbLog.h>
#include <gui/HbLogConfig.h>
#include <ui_HbLogConfigDialog.h>

namespace hb {
namespace log {
/*!
 * TODOC.
 */
class HbLogConfigDialog : public QDialog, private Ui::HbLogConfigDialog {
    Q_OBJECT
    Q_DISABLE_COPY(HbLogConfigDialog)

public:
    HbLogConfigDialog() = delete;
    HbLogConfigDialog(HbLogConfig& pConfig, QWidget* parent = nullptr);
    virtual ~HbLogConfigDialog() = default;

    const HbLogConfig& config() const;

private:
    void saveConfig();
    void updateGui();

    void onFontClicked();
    void onColorClicked(int color_id);
    void onBackgroundColorClicked();
    void onSaveClicked();
    void onResetClicked();
    void onImportClicked();
    void onExportClicked();

    HbLogConfig mConfig;

    QButtonGroup qbg_colors;
    QList<QLineEdit*> qfl_editor_fields; // Use when saving.
};
} // namespace log
} // namespace hb

#endif // HBLOGCONFIGDIALOG_H
