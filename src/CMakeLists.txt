cmake_minimum_required (VERSION 3.8)

add_executable (mesh2voxel "mesh2voxel.cpp" "mesh2voxel.h")
if( NOT $ENV{VULKAN_SDK} STREQUAL "" )
    message( STATUS "Vulkan SDK Directory :" $ENV{VULKAN_SDK})
    target_include_directories(mesh2voxel PUBLIC $ENV{VULKAN_SDK}/include)
else()
    message( FATAL_ERROR "Vulkan SDK not found.")
endif()
