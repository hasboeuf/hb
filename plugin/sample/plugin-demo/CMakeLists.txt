cmake_minimum_required(VERSION 3.5)

project(PluginDemo)

find_package(Qt5 REQUIRED Core Gui Widgets)

set(CMAKE_AUTOMOC ON)
set(AUTOUIC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

file(GLOB PluginDemo_SRC
    "*.h"
    "*.cpp"
)

qt5_wrap_ui(PluginDemo_UI
    forms/AppMainWindow.ui
    forms/PluginListWidget.ui
)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_executable(PluginDemo ${PluginDemo_SRC} ${PluginDemo_UI})

target_link_libraries(PluginDemo Qt5::Core Qt5::Gui Qt5::Widgets PluginInterfaces HbPlugin HbLog HbTools)

install(TARGETS PluginDemo DESTINATION bin)
