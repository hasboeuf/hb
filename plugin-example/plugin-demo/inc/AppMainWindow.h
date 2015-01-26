#ifndef APPMAINWINDOW_H
#define APPMAINWINDOW_H

// Local
#include <AppPlatformService.h>
#include <ui_AppMainWindow.h>

namespace hb
{
    namespace pluginexample
    {
        class AppMainWindow : public QMainWindow, private Ui::AppMainWindow
        {
            Q_OBJECT

        public:
            explicit AppMainWindow(QWidget *parent = nullptr);

        private:
            AppPlatformService mPlatformServices;
        };
    }
}

#endif // APPMAINWINDOW_H
