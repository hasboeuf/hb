cmake_minimum_required(VERSION 3.5)

project(test_HbWebServiceController)

find_package(Qt5 REQUIRED Core Network Test)

set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

add_executable(test_HbWebServiceController test_HbWebServiceController.cpp)

target_link_libraries(test_HbWebServiceController Qt5::Core Qt5::Network Qt5::Test HbTools)

add_test(NAME test_HbWebServiceController COMMAND test_HbWebServiceController)
