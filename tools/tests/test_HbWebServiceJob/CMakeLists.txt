cmake_minimum_required(VERSION 3.5)

project(test_HbWebServiceJob)

find_package(Qt5 REQUIRED Core Network Test)

set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

add_executable(test_HbWebServiceJob test_HbWebServiceJob.cpp)

target_link_libraries(test_HbWebServiceJob Qt5::Core Qt5::Network Qt5::Test HbTools)
