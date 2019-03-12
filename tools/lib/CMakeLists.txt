cmake_minimum_required(VERSION 3.5)

project(HbTools)

find_package(Qt5 REQUIRED Core Widgets Network)

set(CMAKE_AUTOMOC ON)

set(CONFIG_FILE ${CMAKE_CURRENT_BINARY_DIR}/config.h)
configure_file(config.h.in ${CONFIG_FILE} @ONLY)

include_directories(${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR})

file(GLOB_RECURSE SOURCES
    "*.h"
    "*.cpp"
)

list(APPEND SOURCES ${CMAKE_CURRENT_BINARY_DIR}/config.h)

qt5_add_resources(QRC_SRC resources/HbTools.qrc)

add_library(HbTools STATIC ${SOURCES} ${QRC_SRC})
target_include_directories(
    HbTools PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<INSTALL_INTERFACE:include/HbTools>
)
target_link_libraries(HbTools Qt5::Core Qt5::Widgets Qt5::Network)

install(
    TARGETS HbTools
    EXPORT HbTargets
    ARCHIVE DESTINATION "${INSTALL_LIB_DIR}"
)
install(
    DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/
    DESTINATION ${INSTALL_INCLUDE_DIR}/HbTools
    FILES_MATCHING PATTERN "*.h"
    PATTERN "resources" EXCLUDE
    PATTERN "forms" EXCLUDE
)
install(
    FILES ${CONFIG_FILE}
    DESTINATION ${INSTALL_INCLUDE_DIR}/HbTools
)
