# mesh2voxel
Super-fast polygonal mesh voxelizer using geometry shader with [Vulkan](https://www.khronos.org/vulkan/).
The goals of this repository are, os and hardware agnostic, support off-screen computation, minimal cpu usage.

## Getting Started
### Prerequisites
[Vulkan SDK](https://www.lunarg.com/vulkan-sdk/)

### Build
This implementation depends on many external libraries like assimp, cxxopts, glfw, glm.
But you don't have to install the right version of dependencies by yourself.
```
git clone --recursive https://github.com/goldragoon/mesh2voxel.git
cmmake .\
```

### Execute
Make sure that the path of glslc binary from Vulkan SDK is appended to your path varialbe.
To execute the mesh2voxel, 
```
python3 compileShader.py 
cp shaders [mesh2voxel binary location]
mesh2voxel -w -i ..\..\..\data\bunny.ply
```

## License
See the file [LICENSE.md](LICENSE.md).
