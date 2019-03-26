cmake_minimum_required(VERSION 3.5)

project(HbPlugin)

find_package(Qt5 REQUIRED Core)

set(CMAKE_AUTOMOC ON)
set(AUTOUIC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

include_directories(${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR})

file(GLOB_RECURSE HbPlugin_SRC
    "*.h"
    "*.cpp"
)

add_library(HbPlugin STATIC ${HbPlugin_SRC})

target_include_directories(
    HbPlugin PUBLIC
    "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR};${CMAKE_CURRENT_BINARY_DIR}>"
    "$<INSTALL_INTERFACE:include/HbPlugin>"
)

target_link_libraries(HbPlugin Qt5::Core HbLog HbTools)

install(
    TARGETS HbPlugin
    EXPORT HbTargets
    ARCHIVE DESTINATION "${INSTALL_LIB_DIR}"
)
install(
    DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/
    DESTINATION ${INSTALL_INCLUDE_DIR}/HbPlugin
    FILES_MATCHING PATTERN "*.h"
)
