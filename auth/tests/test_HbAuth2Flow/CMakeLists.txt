cmake_minimum_required(VERSION 3.5)

project(test_HbAuth2Flow)

find_package(Qt5 REQUIRED Core Test)

set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

add_executable(test_HbAuth2Flow test_HbAuth2Flow.cpp)

target_link_libraries(test_HbAuth2Flow Qt5::Core Qt5::Test HbAuth HbTools)

add_test(NAME test_HbAuth2Flow COMMAND test_HbAuth2Flow)
