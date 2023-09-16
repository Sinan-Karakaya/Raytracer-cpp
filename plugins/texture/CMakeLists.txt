# This file handles building each task as sub-project.
#
# Each task becomes an independent project in which you can experiment.
#
# Tasks are added as separate sub-projects so as compilation errors in
# one task don't affect another task.

add_subdirectory(chessTexture)
add_subdirectory(noiseTexture)
add_subdirectory(imageTexture)
add_subdirectory(stripTexture)
add_subdirectory(ringTexture)
add_subdirectory(gradientTexture)
add_subdirectory(blendedTexture)

add_dependencies(${PROJECT_NAME} raytracer_chesstexture)
add_dependencies(${PROJECT_NAME} raytracer_noisetexture)
add_dependencies(${PROJECT_NAME} raytracer_imagetexture)
add_dependencies(${PROJECT_NAME} raytracer_striptexture)
add_dependencies(${PROJECT_NAME} raytracer_ringtexture)
add_dependencies(${PROJECT_NAME} raytracer_gradienttexture)
add_dependencies(${PROJECT_NAME} raytracer_blendedtexture)
