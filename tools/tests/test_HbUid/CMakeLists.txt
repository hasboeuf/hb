cmake_minimum_required(VERSION 3.5)

project(test_HbUid)

find_package(Qt5 REQUIRED Core Test)

set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

add_executable(test_HbUid test_HbUid.cpp)

target_link_libraries(test_HbUid Qt5::Core Qt5::Test HbTools)
