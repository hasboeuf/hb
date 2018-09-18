cmake_minimum_required(VERSION 3.5)

project(HbLogViewer)

find_package(Qt5 REQUIRED Core Widgets Xml)

set(CMAKE_AUTOMOC ON)
set(AUTOUIC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

file(GLOB SOURCES
    "*.h"
    "*.cpp"
)

qt5_add_resources(QRC_SRC resources/HbLogViewer.qrc)

qt5_wrap_ui(FORMS
    forms/LogViewer.ui
    forms/LogViewerConfigDialog.ui
    forms/LogViewerMainWindow.ui
    forms/LogViewerTab.ui
)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_executable(HbLogViewer ${QRC_SRC} ${SOURCES} ${FORMS})

target_link_libraries(HbLogViewer Qt5::Core Qt5::Widgets Qt5::Xml HbLog HbTools)

install(TARGETS HbLogViewer DESTINATION bin)
