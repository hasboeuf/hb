cmake_minimum_required(VERSION 3.5)

project(HbLog)

find_package(Qt5 REQUIRED Core Gui Widgets Xml Network)

set(CMAKE_AUTOMOC ON)
set(AUTOUIC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

include_directories(. gui inputs native outputs)

file(GLOB HbLog_SRC
    "*.h"
    "*/*.h"
    "*.cpp"
    "*/*.cpp"
)

qt5_wrap_ui(HbLog_UI
    forms/HbLogConfigDialog.ui
    forms/HbLogWidget.ui
)

qt5_add_resources(QRC_SRC resources/HbLog.qrc)

add_library(HbLog STATIC ${HbLog_SRC} ${QRC_SRC} ${HbLog_UI})

target_include_directories(HbLog INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(HbLog Qt5::Core Qt5::Gui Qt5::Widgets Qt5::Xml Qt5::Network HbTools)

install(TARGETS HbLog DESTINATION lib)
install(DIRECTORY .
        DESTINATION include/HbLog
        FILES_MATCHING PATTERN "*.h"
        PATTERN "resources" EXCLUDE)
