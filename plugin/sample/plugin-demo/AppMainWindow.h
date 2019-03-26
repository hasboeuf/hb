#ifndef APPMAINWINDOW_H
#define APPMAINWINDOW_H

// Local
#include <AppPlatformService.h>
#include <ui_AppMainWindow.h>

namespace hb {
namespace pluginexample {
class AppMainWindow : public QMainWindow, private Ui_AppMainWindow {
    Q_OBJECT

public:
    explicit AppMainWindow(QWidget* parent = nullptr);

    void onLoadClicked();
    void onUnloadClicked();

private:
    AppPlatformService mPlatformServices;
};
} // namespace pluginexample
} // namespace hb

#endif // APPMAINWINDOW_H
