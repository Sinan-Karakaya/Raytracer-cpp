# This file handles building each task as sub-project.
#
# Each task becomes an independent project in which you can experiment.
#
# Tasks are added as separate sub-projects so as compilation errors in
# one task don't affect another task.

cmake_minimum_required(VERSION 3.20.5)

project(raytracer_renderer)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Ofast")

find_package(SFML REQUIRED COMPONENTS graphics window system)

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
add_library(raytracer_renderer SHARED ${SOURCES})
set_target_properties(raytracer_renderer PROPERTIES PREFIX "")

target_include_directories(raytracer_renderer PRIVATE src)
target_include_directories(raytracer_renderer PRIVATE ${CMAKE_SOURCE_DIR}/tools)
target_include_directories(raytracer_renderer PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_include_directories(raytracer_renderer PRIVATE ${SFML_INCLUDE_DIR})

add_subdirectory(dependencies)

target_link_libraries(raytracer_renderer ${SFML_LIBRARIES})
target_link_libraries(raytracer_renderer ImGui-SFML::ImGui-SFML)

set_target_properties(raytracer_renderer PROPERTIES PREFIX "")
