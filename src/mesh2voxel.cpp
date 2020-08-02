// Computer Graphics
#ifdef _MSC_VER
#pragma warning(disable: 4819)
#endif
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <assimp/Importer.hpp>
#include <assimp/Exporter.hpp>
#include <assimp/scene.h> 
#include <assimp/postprocess.h>

// I/O

#include <iostream>
#include <stdexcept>
#include <cstdlib>
#include <cxxopts.hpp>

const uint32_t WIDTH = 800, HEIGHT = 600;
using namespace std;

class Mesh2voxel {
public:
    void run() {
        initWindow();
        initVulkan();
        mainLoop();
        cleanup();
    }

private:
    GLFWwindow* window;

    void initWindow() {
        
        glfwInit();

        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

        window = glfwCreateWindow(WIDTH, HEIGHT, "Mesh2voxel Visualizer", nullptr, nullptr);
        
    }

    void initVulkan() {

    }

    void mainLoop() {
        
        while (!glfwWindowShouldClose(window)) {
            glfwPollEvents();
        }
        
    }

    void cleanup() {
        
        glfwDestroyWindow(window);

        glfwTerminate();
        
    }
};

int main(int argc, char** argv) {

    cxxopts::Options options("mesh2voxel", "Super-fast polygonal mesh voxelizer using geometry shader with Vulkan.");
    options.add_options()
        ("i,input_file", "Location of input file", cxxopts::value<string>()->default_value(""))
        ("o,output_file", "Location of output file", cxxopts::value<string>()->default_value(".\out.ply"))
        ("v,visualizer", "Turn on visualizer", cxxopts::value<bool>()->default_value("false"))
        ;

    auto rslt = options.parse(argc, argv);

    if (!rslt.count("input_file")) {
        cout << "Input file should be provided." << endl;
        return 0;
    }
    
    string input_file = rslt["input_file"].as<string>(); 
    string output_file = rslt["output_file"].as<string>();
    bool visualizer = rslt["visualizer"].as<bool>();

    cout << input_file << " " << output_file << endl;

    // ACTUAL I/O //
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(input_file,
        aiProcess_Triangulate |
        aiProcess_JoinIdenticalVertices |
        aiProcess_SortByPType);

    if (!scene)
    {
        cout << "Fail to load mesh." << endl;
        return false;
    }
   
    aiMesh *mesh = scene->mMeshes[0];
    //cout << mesh->mNumFaces << " " << mesh->mNumVertices;
    Assimp::Exporter exporter;
    cout << "\tExport path: " << output_file << endl;
    aiReturn ret = exporter.Export(scene, "ply", output_file, scene->mFlags);
    cout << exporter.GetErrorString() << endl;


    Mesh2voxel app;
    try {
        app.run();
    }
    catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}