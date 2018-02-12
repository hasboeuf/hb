cmake_minimum_required(VERSION 3.5)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_REQUIRED TRUE)
set(CMAKE_INSTALL_PREFIX ${CMAKE_CURRENT_SOURCE_DIR}/delivery)

add_subdirectory(tools)
add_subdirectory(log)
add_subdirectory(plugin)
add_subdirectory(link)
add_subdirectory(network)
