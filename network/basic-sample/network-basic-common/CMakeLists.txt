cmake_minimum_required(VERSION 3.5)

project(NetworkBasicCommon)

find_package(Qt5 REQUIRED Core Gui Widgets Network)

set(CMAKE_AUTOMOC ON)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

file(GLOB_RECURSE NetworkBasicCommon_SRC
    "*.h"
    "*.cpp"
)

add_library(NetworkBasicCommon STATIC ${NetworkBasicCommon_SRC})

target_include_directories(NetworkBasicCommon INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(NetworkBasicCommon Qt5::Core Qt5::Gui Qt5::Widgets Qt5::Network HbNetwork)
