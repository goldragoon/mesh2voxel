#ifdef _MSC_VER
#pragma warning(disable: 4819)
#endif

// Computer Graphics

#include <assimp/Importer.hpp>
#include <assimp/Exporter.hpp>
#include <assimp/scene.h> 
#include <assimp/postprocess.h>
#include "mesh2voxel.h"

// I/O
#include <iostream>
#include <stdexcept>
#include <cstdlib>
#include <string>
#include <cxxopts.hpp>


using namespace std;

int main(int argc, char** argv) {

    cxxopts::Options options("mesh2voxel", "Super-fast polygonal mesh voxelizer using geometry shader with Vulkan.");
    options.add_options()
        ("i,input_file", "Location of input file", cxxopts::value<string>()->default_value(""))
        ("o,output_file", "Location of output file", cxxopts::value<string>()->default_value("./out.ply"))
        ("w,window", "Turn on the window for visualization", cxxopts::value<bool>()->default_value("false"))
        ;

    string input_file, output_file;
    bool window;
    
    try {
        cxxopts::ParseResult rslt = options.parse(argc, argv);

        input_file = rslt["input_file"].as<string>();
        output_file = rslt["output_file"].as<string>();
        window = rslt["window"].as<bool>();

        if (!(rslt.count("input_file"))) {
            cout << "Input file should be provided." << endl;
            return 0;
        }
    }
    catch (cxxopts::OptionParseException) {
        cout << "CLI argument parse error" << std::endl;
        return 0;
    }
    catch (cxxopts::OptionSpecException) {
        cout << "CLI argument spec error" << std::endl;
        return 0;
    }

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

    aiMesh* mesh = scene->mMeshes[0];
    cout << mesh->mNumFaces << " " << mesh->mNumVertices;

    aiFace* faces = mesh->mFaces;
    /*
    for(int i = 0; i < mesh->mNumFaces; i++)
        cout << faces[i].mNumIndices << std::endl;
        */


    Mesh2voxel app;
    try {
        app.run();
    }
    catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    // Export to 3D model for debugging purpose
    /*
    Assimp::Exporter exporter;
    cout << "\tExport path: " << output_file << endl;
    aiReturn ret = exporter.Export(scene, "ply", output_file, scene->mFlags);
    cout << exporter.GetErrorString() << endl;
    */

    return EXIT_SUCCESS;
}