# This file handles building each task as sub-project.
#
# Each task becomes an independent project in which you can experiment.
#
# Tasks are added as separate sub-projects so as compilation errors in
# one task don't affect another task.

add_subdirectory(cube)
add_subdirectory(sphere)
add_subdirectory(movingSphere)
add_subdirectory(planes)
#add_subdirectory(bvh)
add_subdirectory(cylinder)
add_subdirectory(limitedCylinder)
add_subdirectory(cone)
add_subdirectory(limitedCone)
add_subdirectory(triangle)

add_dependencies(${PROJECT_NAME} raytracer_cube)
add_dependencies(${PROJECT_NAME} raytracer_sphere)
add_dependencies(${PROJECT_NAME} raytracer_movingSphere)
add_dependencies(${PROJECT_NAME} raytracer_plane)
#add_dependencies(${PROJECT_NAME} raytracer_bvh)
add_dependencies(${PROJECT_NAME} raytracer_cylinder)
add_dependencies(${PROJECT_NAME} raytracer_limitedCylinder)
add_dependencies(${PROJECT_NAME} raytracer_cone)
add_dependencies(${PROJECT_NAME} raytracer_limitedCone)
add_dependencies(${PROJECT_NAME} raytracer_triangle)
