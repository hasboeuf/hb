cmake_minimum_required(VERSION 3.5)

project(test_HbWebServiceResult)

find_package(Qt5 REQUIRED Core Network Test)

set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

add_executable(test_HbWebServiceResult test_HbWebServiceResult.cpp)

target_link_libraries(test_HbWebServiceResult Qt5::Core Qt5::Network Qt5::Test HbTools)

add_test(NAME test_HbWebServiceResult COMMAND test_HbWebServiceResult)
