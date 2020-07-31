#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

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
        ("v,visualizer", "Turn on visualizer", cxxopts::value<bool>()->default_value("false"))
        ;

    auto result = options.parse(argc, argv);
    bool visualizer = result["visualizer"].as<bool>();

    cout << visualizer << endl;
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