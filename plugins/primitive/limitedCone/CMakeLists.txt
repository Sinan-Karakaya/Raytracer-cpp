# This file handles building each task as sub-project.
#
# Each task becomes an independent project in which you can experiment.
#
# Tasks are added as separate sub-projects so as compilation errors in
# one task don't affect another task.

cmake_minimum_required(VERSION 3.20.5)

if (NOT EXISTS "/opt/nvidia/hpc_sdk/Linux_x86_64/23.3/compilers/bin/nvc++")
    set(CMAKE_CXX_STANDARD 17)
    set(CMAKE_CXX_EXTENSIONS OFF)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")
else ()
    # Adjust the GPU architecture according to your target
    set(CMAKE_CXX_COMPILER /opt/nvidia/hpc_sdk/Linux_x86_64/23.3/compilers/bin/nvc++)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdpar=gpu")
endif()

file(GLOB_RECURSE SOURCES "src/*.cpp")
add_library(raytracer_limitedCone SHARED ${SOURCES})
set_target_properties(raytracer_limitedCone PROPERTIES PREFIX "")

target_include_directories(raytracer_limitedCone PRIVATE src)
target_include_directories(raytracer_limitedCone PRIVATE ${CMAKE_SOURCE_DIR}/tools)
target_include_directories(raytracer_limitedCone PRIVATE ${CMAKE_SOURCE_DIR}/include)
