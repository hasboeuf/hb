cmake_minimum_required(VERSION 3.5)

add_subdirectory(lib)
if(NOT HB_MINIMAL_BUILD)
    add_subdirectory(sample)
endif()

