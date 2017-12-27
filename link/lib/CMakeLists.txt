cmake_minimum_required(VERSION 3.5)

project(HbLink)

find_package(Qt5 REQUIRED Core Network)

set(CMAKE_AUTOMOC ON)

include_directories(. config facebook google)

file(GLOB HbLink_SRC
    "*.h"
    "*/*.h"
    "*.cpp"
    "*/*.cpp"
)

add_library(HbLink STATIC ${HbLink_SRC})

target_include_directories(HbLink INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(HbLink Qt5::Core Qt5::Network HbTools HbLog)

install(TARGETS HbLink DESTINATION lib)
install(DIRECTORY .
        DESTINATION include/HbLink
        FILES_MATCHING PATTERN "*.h"
)
