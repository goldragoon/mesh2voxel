﻿# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.8)

project ("mesh2voxel")
find_package(Vulkan REQUIRED)



# The main executable.
add_executable (mesh2voxel "src/main.cpp" "src/mesh2voxel.cpp" "src/mesh2voxel.h"  )
set_property(TARGET mesh2voxel PROPERTY CXX_STANDARD 17)
# based on FindVulkan.cmake
if(${Vulkan_FOUND})
    message( STATUS "Vulkan SDK directory is " ${Vulkan_INCLUDE_DIRS})
    target_include_directories(mesh2voxel PUBLIC ${Vulkan_INCLUDE_DIRS})
    target_link_libraries(mesh2voxel PRIVATE ${Vulkan_LIBRARY})
else()
    message( FATAL_ERROR "Vulkan SDK not found.")
endif()

# glfw
add_subdirectory("lib/glfw" EXCLUDE_FROM_ALL)
target_link_libraries(mesh2voxel PRIVATE glfw)

# cxxopts
add_subdirectory("lib/cxxopts" EXCLUDE_FROM_ALL)
target_link_libraries(mesh2voxel PRIVATE cxxopts)

# assimp
add_subdirectory("lib/assimp" EXCLUDE_FROM_ALL)
target_link_libraries(mesh2voxel PRIVATE assimp)

# glm
add_subdirectory("lib/glm" EXCLUDE_FROM_ALL)
target_link_libraries(mesh2voxel PRIVATE glm)