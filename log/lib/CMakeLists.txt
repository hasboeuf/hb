cmake_minimum_required(VERSION 3.5)

project(HbLog)

find_package(Qt5 REQUIRED Core Gui Widgets Xml Network)

set(CMAKE_AUTOMOC ON)
set(AUTOUIC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

file(GLOB_RECURSE HbLog_SRC
    "*.h"
    "*.cpp"
)

qt5_wrap_ui(HbLog_UI
    forms/HbLogConfigDialog.ui
    forms/HbLogWidget.ui
)

qt5_add_resources(QRC_SRC resources/HbLog.qrc)

add_library(HbLog STATIC ${HbLog_SRC} ${QRC_SRC} ${HbLog_UI})

target_include_directories(
    HbLog PUBLIC
    "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR};${CMAKE_CURRENT_BINARY_DIR}>"
    "$<INSTALL_INTERFACE:include/HbLog>"
)

target_link_libraries(HbLog Qt5::Core Qt5::Gui Qt5::Widgets Qt5::Xml Qt5::Network HbTools)

install(
    TARGETS HbLog
    EXPORT HbTargets
    ARCHIVE DESTINATION "${INSTALL_LIB_DIR}"
)
install(
    DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/
    DESTINATION ${INSTALL_INCLUDE_DIR}/HbLog
    FILES_MATCHING PATTERN "*.h"
    PATTERN "resources" EXCLUDE
    PATTERN "forms" EXCLUDE
)

file(GLOB UI_HEADERS "${CMAKE_CURRENT_BINARY_DIR}/*.h")
install(
    FILES ${UI_HEADERS}
    DESTINATION ${INSTALL_INCLUDE_DIR}/HbLog
)
