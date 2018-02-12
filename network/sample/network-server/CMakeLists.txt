cmake_minimum_required(VERSION 3.5)

project(NetworkServer)

find_package(Qt5 REQUIRED Core Gui Widgets Network)

set(CMAKE_AUTOMOC ON)
set(AUTOUIC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

file(GLOB NetworkServer_SRC
    "*.h"
    "*.cpp"
)

qt5_wrap_ui(NetworkServer_UI
    forms/ServerMainWindow.ui
)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_executable(NetworkServer ${NetworkServer_SRC} ${NetworkServer_UI})

target_link_libraries(NetworkServer Qt5::Core Qt5::Gui Qt5::Widgets Qt5::Network NetworkCommon HbNetwork HbLink HbLog HbTools)
