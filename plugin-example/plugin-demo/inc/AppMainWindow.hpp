#ifndef APPMAINWINDOW_HPP
#define APPMAINWINDOW_HPP

#include "ui_AppMainWindow.h"
#include "AppPlatformService.hpp"

class AppMainWindow : public QMainWindow, private Ui::AppMainWindow
{
    Q_OBJECT

public:
    explicit AppMainWindow(QWidget *parent = 0);

private:
    AppPlatformService mPlatformServices;
};

#endif // APPMAINWINDOW_HPP
