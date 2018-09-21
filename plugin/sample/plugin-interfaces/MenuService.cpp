// Qt
#include <QtWidgets/QAction>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
// Local
#include <AppPlatformService.h>
#include <MenuService.h>

using namespace hb::pluginexample;

MenuService::MenuService(QMenuBar* menuBar) : AppService(AppPlatformService::SERVICE_MENU_BAR, "0.0.1") {
    mMenuBar = menuBar;
    mCurrentMenuId = MENU_USER;

    if (mMenuBar) {
        QList<QMenu*> menus = mMenuBar->findChildren<QMenu*>();
        for (QMenu* menu : menus) {
            if (menu->title() == QStringLiteral("File"))
                mMenus.insert(MENU_FILE, menu);
            else if (menu->title() == QStringLiteral("Edit"))
                mMenus.insert(MENU_EDIT, menu);
            else if (menu->title() == QStringLiteral("Tools"))
                mMenus.insert(MENU_TOOLS, menu);
            else if (menu->title() == QStringLiteral("Window"))
                mMenus.insert(MENU_WINDOW, menu);
            else if (menu->title() == QStringLiteral("Plugins"))
                mMenus.insert(MENU_PLUGINS, menu);
            else if (menu->title() == QStringLiteral("Help"))
                mMenus.insert(MENU_HELP, menu);
        }
    }
}

int MenuService::addMenu(qint32 menu_parent_id, const QString& title) {
    if (!mMenuBar)
        return -1;

    if (menu_parent_id == MENU_NEW) {
        QMenu* menu_new = mMenuBar->addMenu(title);
        qint32 menu_id = mCurrentMenuId++;

        mMenus.insert(menu_id, menu_new);

        return menu_id;
    }

    if (mMenus.contains(menu_parent_id) && mMenus.value(menu_parent_id)) {
        QMenu* menu_parent = mMenus.value(menu_parent_id);
        QMenu* menu_new = menu_parent->addMenu(title);
        qint32 menu_id = mCurrentMenuId++;

        mMenus.insert(menu_id, menu_new);

        return menu_id;
    }

    return -1;
}

QAction* MenuService::addItem(qint32 menu_id, const QString& title) {
    if (!mMenus.contains(menu_id) || !mMenus.value(menu_id)) {
        return nullptr;
    }

    QMenu* menu = mMenus.value(menu_id);
    QAction* action = menu->addAction(title);

    return action;
}
