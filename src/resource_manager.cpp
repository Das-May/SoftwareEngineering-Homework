#include "resource_manager.h"

#include <iostream>
#include <sstream>
#include <fstream>

#define STB_IMAGE_IMPLEMENTATION //定义STB_IMAGE_IMPLEMENTATION，预处理器会修改头文件，让其只包含相关的函数定义源码，相当于把.h文件变成.cpp文件
#include "stb_image.h"

// 实例化静态变量
std::map<std::string, Shader>       ResourceManager::Shaders;
std::map<std::string, Texture2D>    ResourceManager::Textures;


Shader ResourceManager::LoadShader(const char* vShaderFile, const char* fShaderFile, const char* gShaderFile, std::string name)
{
    Shaders[name] = loadShaderFromFile(vShaderFile, fShaderFile, gShaderFile);
    return Shaders[name];
}

Shader ResourceManager::GetShader(std::string name)
{
    return Shaders[name];
}

Texture2D ResourceManager::LoadTexture(const char* file, bool alpha, std::string name)
{
    Textures[name] = loadTextureFromFile(file, alpha);
    return Textures[name];
}

Texture2D ResourceManager::GetTexture(std::string name)
{
    return Textures[name];
}

void ResourceManager::Clear()
{
    // (properly) delete all shaders删除所有着色器	
    for (auto iter : Shaders)
        glDeleteProgram(iter.second.ID);
}

Shader ResourceManager::loadShaderFromFile(const char* vShaderFile, const char* fShaderFile, const char* gShaderFile)
{
    // 1. retrieve the vertex/fragment source code from filePath
    std::string vertexCode;
    std::string fragmentCode;
    std::string geometryCode;
    try
    {
        // open files
        std::ifstream vertexShaderFile(vShaderFile);
        std::ifstream fragmentShaderFile(fShaderFile);
        std::stringstream vShaderStream, fShaderStream;
        // read file's buffer contents into streams
        vShaderStream << vertexShaderFile.rdbuf();
        fShaderStream << fragmentShaderFile.rdbuf();
        // close file handlers
        vertexShaderFile.close();
        fragmentShaderFile.close();
        // convert stream into string
        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();
        // if geometry shader path is present, also load a geometry shader
        if (gShaderFile != nullptr)
        {
            std::ifstream geometryShaderFile(gShaderFile);
            std::stringstream gShaderStream;
            gShaderStream << geometryShaderFile.rdbuf();
            geometryShaderFile.close();
            geometryCode = gShaderStream.str();
        }
    }
    catch (std::exception e)
    {
        std::cout << "ERROR::SHADER: Failed to read shader files" << std::endl;
    }
    const char* vShaderCode = vertexCode.c_str();
    const char* fShaderCode = fragmentCode.c_str();
    const char* gShaderCode = geometryCode.c_str();
    // 2. now create shader object from source code
    Shader shader;
    shader.Compile(vShaderCode, fShaderCode, gShaderFile != nullptr ? gShaderCode : nullptr);
    return shader;
}

Texture2D ResourceManager::loadTextureFromFile(const char* file, bool alpha)
{
    // 创建纹理对象
    Texture2D texture;
    if (alpha)
    {
        texture.Internal_Format = GL_RGBA;
        texture.Image_Format = GL_RGBA;
    }
    // 加载图像数据（是char数组）
    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true);//翻转图片y轴
    unsigned char* data = stbi_load(file, &width, &height, &nrChannels, 0);
    if (data)
    {
        // 交给纹理对象，生成纹理
        texture.Generate(width, height, data);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    // 释放图像数据
    stbi_image_free(data);
    return texture;
}