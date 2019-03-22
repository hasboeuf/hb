cmake_minimum_required(VERSION 3.5)

add_subdirectory(lib)
add_subdirectory(viewer)
if(NOT HB_MINIMAL_BUILD)
    add_subdirectory(sample)
    add_subdirectory(tests/test_HbLogArgumentParser)
endif()
