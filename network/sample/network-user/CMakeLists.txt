cmake_minimum_required(VERSION 3.5)

project(NetworkUser)

find_package(Qt5 REQUIRED Core Gui Widgets Network)

set(CMAKE_AUTOMOC ON)
set(AUTOUIC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

file(GLOB NetworkUser_SRC
    "*.h"
    "*.cpp"
)

qt5_wrap_ui(NetworkUser_UI
    forms/UserMainWindow.ui
)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_executable(NetworkUser ${NetworkUser_SRC} ${NetworkUser_UI})

target_link_libraries(NetworkUser Qt5::Core Qt5::Gui Qt5::Widgets Qt5::Network NetworkCommon HbNetwork HbLink HbLog HbTools)

install(TARGETS NetworkUser DESTINATION bin)
