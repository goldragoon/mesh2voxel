import os

shaderPath = "shader"
shaders = os.listdir("shader")
for shader in shaders:
    fullShaderPath = os.path.join(shaderPath, shader)
    name, extension = fullShaderPath.split(".", 1)
    
    if extension == "spv":
        continue

    print(name, extension)
    os.system("glslc {} -o {}.spv".format(fullShaderPath, name))
