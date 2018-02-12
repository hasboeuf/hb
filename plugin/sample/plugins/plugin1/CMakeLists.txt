cmake_minimum_required(VERSION 3.5)

project(Plugin1)

find_package(Qt5 REQUIRED Core)

set(CMAKE_AUTOMOC ON)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

file(GLOB_RECURSE Plugin1_SRC
    "*.h"
    "*.cpp"
)

add_library(Plugin1 SHARED ${Plugin1_SRC})

target_link_libraries(Plugin1 Qt5::Core PluginInterfaces HbPlugin)
