cmake_minimum_required(VERSION 3.5)

add_subdirectory(lib)
if(NOT HB_MINIMAL_BUILD)
    add_subdirectory(sample/plugin-interfaces)
    add_subdirectory(sample/plugins/plugin1)
    add_subdirectory(sample/plugins/plugin2)
    add_subdirectory(sample/plugin-demo)
endif()
