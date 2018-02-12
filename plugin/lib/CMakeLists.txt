cmake_minimum_required(VERSION 3.5)

project(HbPlugin)

find_package(Qt5 REQUIRED Core Gui Widgets)

set(CMAKE_AUTOMOC ON)
set(AUTOUIC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

include_directories(${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR})

file(GLOB_RECURSE HbPlugin_SRC
    "*.h"
    "*.cpp"
)

qt5_wrap_ui(HbPlugin_UI
    forms/HbPluginListWidget.ui
)

add_library(HbPlugin STATIC ${HbPlugin_SRC} ${HbPlugin_UI})

target_include_directories(HbPlugin INTERFACE ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR})

target_link_libraries(HbPlugin Qt5::Core Qt5::Gui Qt5::Widgets HbLog HbTools)

install(TARGETS HbPlugin DESTINATION lib)
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/
        DESTINATION include/HbPlugin
        FILES_MATCHING PATTERN "*.h"
)

file(GLOB UI_HEADERS "${CMAKE_CURRENT_BINARY_DIR}/*.h")
install(FILES ${UI_HEADERS}
        DESTINATION include/HbPlugin)
