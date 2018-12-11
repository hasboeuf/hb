#ifndef LOGVIEWERMAINWINDOW_H
#define LOGVIEWERMAINWINDOW_H

// Local
#include <ui_LogViewerMainWindow.h>

namespace hb {
namespace logviewer {

class LogViewerMainWindow : public QMainWindow, private Ui::LogViewerMainWindow {
    Q_OBJECT
    Q_DISABLE_COPY(LogViewerMainWindow)

public:
    LogViewerMainWindow(QWidget* parent = nullptr);
    virtual ~LogViewerMainWindow() = default;

private:
    LogViewerConfig* mConfig;
};
} // namespace logviewer
} // namespace hb

#endif // LOGVIEWERMAINWINDOW_H
