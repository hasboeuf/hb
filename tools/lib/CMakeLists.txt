cmake_minimum_required(VERSION 3.5)

project(HbTools)

find_package(Qt5 REQUIRED Core Widgets)

set(CMAKE_AUTOMOC ON)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

file(GLOB_RECURSE HbTools_SRC
    "*.h"
    "*.cpp"
)

qt5_add_resources(QRC_SRC resources/HbTools.qrc)

add_library(HbTools STATIC ${HbTools_SRC} ${QRC_SRC})

target_include_directories(HbTools INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(HbTools Qt5::Core Qt5::Widgets)

install(TARGETS HbTools DESTINATION lib)
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/
        DESTINATION include/HbTools
        FILES_MATCHING PATTERN "*.h"
        PATTERN "resources" EXCLUDE
        PATTERN "forms" EXCLUDE)
