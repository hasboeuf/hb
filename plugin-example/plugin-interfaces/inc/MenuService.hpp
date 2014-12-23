#ifndef MENUSERVICE_HPP
#define MENUSERVICE_HPP

#include "AppService.hpp"

#include <QtCore/QHash>

class QMenuBar;
class QMenu;
class QAction;

class MenuService : public AppService
{
    Q_OBJECT

public:
    enum MenuID
    {
        MENU_NEW  = 0,
        MENU_FILE,
        MENU_EDIT,
        MENU_TOOLS,
        MENU_WINDOW,
        MENU_PLUGINS,
        MENU_HELP,
        MENU_USER
    };

    MenuService(QString name, QString version, QMenuBar* menuBar);

    int       addMenu  (int menu_parent, QString title);
    QAction*  addItem  (int menu_id,     QString title);

private:
    QMenuBar*          mMenuBar;
    int                mCurrentMenuID;
    QHash<int, QMenu*> mMenus;
};

#endif // MENUSERVICE_HPP
