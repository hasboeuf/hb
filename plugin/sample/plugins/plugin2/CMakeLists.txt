cmake_minimum_required(VERSION 3.5)

project(Plugin2)

find_package(Qt5 REQUIRED Core)

set(CMAKE_AUTOMOC ON)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

file(GLOB_RECURSE Plugin2_SRC
    "*.h"
    "*.cpp"
)

add_library(Plugin2 SHARED ${Plugin2_SRC})

target_link_libraries(Plugin2 Qt5::Core PluginInterfaces HbPlugin)
