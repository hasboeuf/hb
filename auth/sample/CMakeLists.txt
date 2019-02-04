cmake_minimum_required(VERSION 3.5)

project(AuthSample)

find_package(Qt5 REQUIRED Core Gui Widgets Xml Network NetworkAuth)

set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

file(GLOB AuthSample_SRC
    "*.h"
    "*.cpp"
)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_executable(AuthSample ${AuthSample_SRC})

target_link_libraries(AuthSample Qt5::Core Qt5::Gui Qt5::Widgets Qt5::Xml Qt5::Network Qt5::NetworkAuth HbAuth HbLog HbTools)

install(TARGETS AuthSample DESTINATION bin)
