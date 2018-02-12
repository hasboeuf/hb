cmake_minimum_required(VERSION 3.5)

project(LinkSample)

find_package(Qt5 REQUIRED Core Gui Widgets Xml Network)

set(CMAKE_AUTOMOC ON)
set(AUTOUIC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

file(GLOB LinkSample_SRC
    "*.h"
    "*.cpp"
)

qt5_wrap_ui(LinkSample_UI
    forms/LinkMainWindow.ui
)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_executable(LinkSample ${LinkSample_SRC} ${LinkSample_UI})

target_link_libraries(LinkSample Qt5::Core Qt5::Gui Qt5::Widgets Qt5::Xml Qt5::Network HbLink HbLog HbTools)
