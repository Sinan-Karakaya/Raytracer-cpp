# This file handles building each task as sub-project.
#
# Each task becomes an independent project in which you can experiment.
#
# Tasks are added as separate sub-projects so as compilation errors in
# one task don't affect another task.

add_subdirectory(dielectric)
add_subdirectory(metal)
add_subdirectory(diffuseLight)

add_dependencies(${PROJECT_NAME} raytracer_dielectric)
add_dependencies(${PROJECT_NAME} raytracer_metal)
add_dependencies(${PROJECT_NAME} raytracer_diffuselight)
