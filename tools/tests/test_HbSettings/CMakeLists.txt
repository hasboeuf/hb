cmake_minimum_required(VERSION 3.5)

project(test_HbSettings)

find_package(Qt5 REQUIRED Core Test)

set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

add_executable(test_HbSettings test_HbSettings.cpp)

target_link_libraries(test_HbSettings Qt5::Core Qt5::Test HbTools)
