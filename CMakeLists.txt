cmake_minimum_required(VERSION 3.5)

set(CMAKE_INSTALL_PREFIX ${CMAKE_CURRENT_SOURCE_DIR}/delivery)

project(Hb)

set(HB_MAJOR_VERSION 1)
set(HB_MINOR_VERSION 1)
set(HB_PATCH_VERSION 0)
set(HB_VERSION ${HB_MAJOR_VERSION}.${HB_MINOR_VERSION}.${HB_PATCH_VERSION})

add_compile_options(-DQT_DISABLE_DEPRECATED_BEFORE=0x051000)
add_compile_options(-Werror=switch)
add_compile_options(-Werror=return-type)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_REQUIRED TRUE)

set(INSTALL_LIB_DIR lib CACHE INTERNAL "Installation directory for libraries")
set(INSTALL_BIN_DIR bin CACHE INTERNAL "Installation directory for executables")
set(INSTALL_INCLUDE_DIR include CACHE INTERNAL "Installation directory for header files")
set(INSTALL_CMAKE_DIR cmake CACHE INTERNAL "Installation directory for CMake files")

# Make relative paths absolute
foreach(p LIB BIN INCLUDE CMAKE)
    set(var INSTALL_${p}_DIR)
    if(NOT IS_ABSOLUTE "${${var}}")
        set(${var} "${CMAKE_INSTALL_PREFIX}/${${var}}")
    endif()
endforeach()

add_subdirectory(tools)
add_subdirectory(log)
#add_subdirectory(plugin)
#add_subdirectory(link)
#add_subdirectory(network)

# Add all targets to the build-tree export set
#export(TARGETS HbTools HbLog HbPlugin HbLink HbNetwork FILE "${PROJECT_BINARY_DIR}/HbTargets.cmake")

# Create the HbConfig.cmake and HbConfigVersion files
file(RELATIVE_PATH REL_INCLUDE_DIR "${INSTALL_CMAKE_DIR}" "${INSTALL_INCLUDE_DIR}")
set(CONF_INCLUDE_DIRS "${REL_INCLUDE_DIR}")
configure_file(HbConfig.cmake.in "${PROJECT_BINARY_DIR}/HbConfig.cmake" @ONLY)
configure_file(HbConfigVersion.cmake.in "${PROJECT_BINARY_DIR}/HbConfigVersion.cmake" @ONLY)

# Install the HbConfig.cmake and HbConfigVersion.cmake
install(FILES
  "${PROJECT_BINARY_DIR}/HbConfig.cmake"
  "${PROJECT_BINARY_DIR}/HbConfigVersion.cmake"
  DESTINATION "${INSTALL_CMAKE_DIR}")

# Install the export set for use with the install-tree
install(EXPORT HbTargets DESTINATION
  "${INSTALL_CMAKE_DIR}")
