cmake_minimum_required(VERSION 3.5)

project(test_HbSingleApplication)

find_package(Qt5 REQUIRED Core Test)

set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

add_executable(test_HbSingleApplication test_HbSingleApplication.cpp)

target_link_libraries(test_HbSingleApplication Qt5::Core Qt5::Test HbTools)

add_test(NAME test_HbSingleApplication COMMAND test_HbSingleApplication)
