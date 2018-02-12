cmake_minimum_required(VERSION 3.5)

project(NetworkBasicUser)

find_package(Qt5 REQUIRED Core Gui Widgets Network)

set(CMAKE_AUTOMOC ON)
set(AUTOUIC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

file(GLOB NetworkBasicUser_SRC
    "*.h"
    "*.cpp"
)

qt5_wrap_ui(NetworkBasicUser_UI
    forms/BasicUserMainWindow.ui
)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_executable(NetworkBasicUser ${NetworkBasicUser_SRC} ${NetworkBasicUser_UI})

target_link_libraries(NetworkBasicUser Qt5::Core Qt5::Gui Qt5::Widgets Qt5::Network NetworkBasicCommon HbNetwork HbLink HbLog HbTools)
