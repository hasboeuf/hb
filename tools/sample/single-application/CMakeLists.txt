cmake_minimum_required(VERSION 3.5)

project(SingleApplication)

find_package(Qt5 REQUIRED Core)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

file(GLOB SingleApplication_SRC
    "*.h"
    "*.cpp"
)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_executable(SingleApplication ${SingleApplication_SRC})

target_link_libraries(SingleApplication Qt5::Core HbTools)

install(TARGETS SingleApplication DESTINATION bin)
