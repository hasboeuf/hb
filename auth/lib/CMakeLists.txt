cmake_minimum_required(VERSION 3.5)

project(HbAuth)

find_package(Qt5 REQUIRED Core Network NetworkAuth)

set(CMAKE_AUTOMOC ON)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

file(GLOB_RECURSE HbAuth_SRC
    "*.h"
    "*.cpp"
)

qt5_add_resources(QRC_SRC resources/HbAuth.qrc)

add_library(HbAuth STATIC ${QRC_SRC} ${HbAuth_SRC})

target_include_directories(
    HbAuth PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<INSTALL_INTERFACE:include/HbAuth>
)

target_link_libraries(HbAuth Qt5::Core Qt5::Network Qt5::NetworkAuth HbLog HbTools)

install(
    TARGETS HbAuth
    EXPORT HbTargets
    ARCHIVE DESTINATION "${INSTALL_LIB_DIR}"
)
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/
        DESTINATION ${INSTALL_INCLUDE_DIR}/HbAuth
        FILES_MATCHING PATTERN "*.h"
)
