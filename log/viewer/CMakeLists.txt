cmake_minimum_required(VERSION 3.5)

project(HbLogViewer)

find_package(Qt5 REQUIRED Core Widgets Xml)

set(CMAKE_AUTOMOC ON)
set(AUTOUIC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

file(GLOB HbLogViewer_SRC
    "*.h"
    "*.cpp"
)

qt5_wrap_ui(HbLogViewer_UI
    forms/LogViewer.ui
    forms/LogViewerConfigDialog.ui
    forms/LogViewerMainWindow.ui
    forms/LogViewerTab.ui
)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_executable(HbLogViewer ${HbLogViewer_SRC} ${HbLogViewer_UI})

target_link_libraries(HbLogViewer Qt5::Core Qt5::Widgets Qt5::Xml HbLog HbTools)

install(TARGETS HbLogViewer DESTINATION bin)
