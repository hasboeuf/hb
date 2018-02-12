cmake_minimum_required(VERSION 3.5)

project(HbNetwork)

find_package(Qt5 REQUIRED Core Network)

set(CMAKE_AUTOMOC ON)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

file(GLOB_RECURSE HbNetwork_SRC
    "*.h"
    "*.cpp"
)

add_library(HbNetwork STATIC ${HbNetwork_SRC})

target_include_directories(HbNetwork INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(HbNetwork Qt5::Core Qt5::Network HbLink HbLog HbTools)

install(TARGETS HbNetwork DESTINATION lib)
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/
        DESTINATION include/HbNetwork
        FILES_MATCHING PATTERN "*.h")
