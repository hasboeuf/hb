#include "MenuService.hpp"

#include <QtWidgets/QMenuBar>
#include <QtWidgets/QMenu>
#include <QtWidgets/QAction>

MenuService::MenuService(QString name, QString version, QMenuBar* menuBar) :
    AppService(name, version)
{
    mMenuBar = menuBar;
    mCurrentMenuID = MENU_USER;

    if(mMenuBar)
    {
        QList<QMenu*> menus = mMenuBar->findChildren<QMenu*>();
        foreach(QMenu* menu, menus)
        {
            if     (menu->title() == "File"   ) mMenus.insert(MENU_FILE,    menu);
            else if(menu->title() == "Edit"   ) mMenus.insert(MENU_EDIT,    menu);
            else if(menu->title() == "Tools"  ) mMenus.insert(MENU_TOOLS,   menu);
            else if(menu->title() == "Window" ) mMenus.insert(MENU_WINDOW,  menu);
            else if(menu->title() == "Plugins") mMenus.insert(MENU_PLUGINS, menu);
            else if(menu->title() == "Help"   ) mMenus.insert(MENU_HELP,    menu);

        }
    }
}

int MenuService::addMenu  (int menu_parent_id, QString title)
{
    if(!mMenuBar) return -1;

    if(menu_parent_id == MENU_NEW)
    {
        QMenu* menu_new = mMenuBar->addMenu(title);
        int    menu_id  = mCurrentMenuID++;

        mMenus.insert(menu_id, menu_new);

        return menu_id;
    }

    if(mMenus.contains(menu_parent_id) && mMenus.value(menu_parent_id))
    {
        QMenu* menu_parent = mMenus.value(menu_parent_id);
        QMenu* menu_new    = menu_parent->addMenu(title);
        int menu_id        = mCurrentMenuID++;

        mMenus.insert(menu_id, menu_new);

        return menu_id;
    }

    return -1;
}

QAction* MenuService::addItem  (int menu_id, QString title)
{
    if(!mMenus.contains(menu_id) || !mMenus.value(menu_id))
    {
        return 0;
    }

    QMenu*   menu   = mMenus.value(menu_id);
    QAction* action = menu->addAction(title);

    return action;
}

