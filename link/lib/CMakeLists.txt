cmake_minimum_required(VERSION 3.5)

project(HbLink)

find_package(Qt5 REQUIRED Core Network)

set(CMAKE_AUTOMOC ON)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

file(GLOB_RECURSE HbLink_SRC
    "*.h"
    "*.cpp"
)

add_library(HbLink STATIC ${HbLink_SRC})

target_include_directories(
    HbLink PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<INSTALL_INTERFACE:include/HbLink>
)

target_link_libraries(HbLink Qt5::Core Qt5::Network HbLog HbTools)

install(
    TARGETS HbLink
    EXPORT HbTargets
    ARCHIVE DESTINATION "${INSTALL_LIB_DIR}"
)
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/
        DESTINATION ${INSTALL_INCLUDE_DIR}/HbLink
        FILES_MATCHING PATTERN "*.h"
)
