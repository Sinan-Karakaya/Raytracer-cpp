cmake_minimum_required(VERSION 3.0)

if (NOT EXISTS "/opt/nvidia/hpc_sdk/Linux_x86_64/23.3/compilers/bin/nvc++")
    message(STATUS "NVC++ not found. Compiling as CPU-only.")
    set(CMAKE_CXX_STANDARD 17)
    set(CMAKE_CXX_EXTENSIONS OFF)
    set(CMAKE_CXX_STANDARD_REQUIRED ON)
else ()
    # Adjust the GPU architecture according to your target
    message(STATUS "NVC++ found. Compiling as GPU-enabled.")
    set(CMAKE_CXX_COMPILER /opt/nvidia/hpc_sdk/Linux_x86_64/23.3/compilers/bin/nvc++)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdpar=gpu")
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fdiagnostics-color=always")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

project(raytracer)

# ///////////////////////////////// LIBCONFIG

find_package(PkgConfig REQUIRED)
pkg_check_modules(LIBCONFIG REQUIRED libconfig++)

get_property(targets DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY BUILDSYSTEM_TARGETS)
foreach(target ${targets})
    # Check if the target is a library
    if(TARGET ${target} AND (${target} MATCHES "^lib"))
        # Remove the "lib" prefix from the library name
        set_target_properties(${target} PROPERTIES PREFIX "")
    endif()
endforeach()

# ///////////////////////////////// LIBCONFIG

include_directories(include)
include_directories(tools)
include_directories(src)
include_directories(src/LibLoader)
include_directories(src/Parser)
include_directories(src/Builder)
include_directories(src/Camera)
include_directories(plugins/renderer/src)

file(GLOB_RECURSE SOURCES "src/*.cpp")
add_executable(raytracer ${SOURCES})

# Link against libconfig++
target_link_libraries(raytracer ${LIBCONFIG_LIBRARIES})

# Link against libdl
target_link_libraries(raytracer dl)

# Link against libpthread
target_link_libraries(raytracer pthread)

# Include the libconfig++ headers
target_include_directories(raytracer PRIVATE ${LIBCONFIG_INCLUDE_DIRS})

# add plugins
add_subdirectory(plugins/renderer)
add_subdirectory(plugins/primitive)
add_subdirectory(plugins/material)
add_subdirectory(plugins/texture)
add_dependencies(raytracer raytracer_renderer)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/config DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
