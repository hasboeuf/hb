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

target_include_directories(HbLink INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(HbLink Qt5::Core Qt5::Network HbLog HbTools)

install(TARGETS HbLink DESTINATION lib)
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/
        DESTINATION include/HbLink
        FILES_MATCHING PATTERN "*.h"
)
