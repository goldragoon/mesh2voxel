# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.8)

project ("mesh2voxel")
find_package(Vulkan REQUIRED)

# The main executable.
add_executable (mesh2voxel "src/mesh2voxel.cpp" "src/mesh2voxel.h")
if( NOT $ENV{VULKAN_SDK} STREQUAL "" )
    message( STATUS "Vulkan SDK Directory :" $ENV{VULKAN_SDK})
    target_include_directories(mesh2voxel PUBLIC $ENV{VULKAN_SDK}/include)
else()
    message( FATAL_ERROR "Vulkan SDK not found.")
endif()


# GLFW
add_subdirectory("lib/glfw" EXCLUDE_FROM_ALL)
target_link_libraries(mesh2voxel PRIVATE glfw)