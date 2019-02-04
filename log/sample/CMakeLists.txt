cmake_minimum_required(VERSION 3.5)

project(LogSample)

find_package(Qt5 REQUIRED Core)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

file(GLOB LogSample_SRC
    "*.h"
    "*.cpp"
)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_executable(LogSample ${LogSample_SRC})

target_link_libraries(LogSample Qt5::Core HbLog HbTools)

install(TARGETS LogSample DESTINATION bin)
