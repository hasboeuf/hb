cmake_minimum_required(VERSION 3.5)

project(test_Parser)

find_package(Qt5 REQUIRED Core Test)

set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

add_executable(test_Parser test_Parser.cpp)

target_link_libraries(test_Parser Qt5::Core Qt5::Test HbTools)
