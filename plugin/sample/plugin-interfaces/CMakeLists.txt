cmake_minimum_required(VERSION 3.5)

project(PluginInterfaces)

find_package(Qt5 REQUIRED Core)

set(CMAKE_AUTOMOC ON)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

file(GLOB PluginInterfaces_SRC
    "*.h"
    "*.cpp"
)

add_library(PluginInterfaces STATIC ${PluginInterfaces_SRC})

target_include_directories(PluginInterfaces INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(PluginInterfaces Qt5::Core HbPlugin)
