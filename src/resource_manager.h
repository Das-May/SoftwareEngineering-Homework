#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include <map>
#include <string>

#include <glad/glad.h>

#include "shader.h"
#include "texture.h"

// 单例模式
// 加载并按照命名来存储 着色器/纹理/模型
// 所有的功能和资源都是静态的
// 没有公有的构造器
class ResourceManager
{
public:
    // 把所有资源存储在字典中，以命名查找
    static std::map<std::string, Shader>    Shaders;
    static std::map<std::string, Texture2D>    Textures;
    // 从文件中加载着色器
    static Shader    LoadShader(const char* vShaderFile, const char* fShaderFile, const char* gShaderFile, std::string name);
    // 检索（获取）已存储的着色器
    static Shader    GetShader(std::string name);
    // 从文件中加载纹理
    static Texture2D LoadTexture(const char* file, bool alpha, std::string name);
    // 检索一个已存储的纹理
    static Texture2D GetTexture(std::string name);
    // 正确地分配所有已加载的资源
    static void      Clear();
private:
    // 私有构造函数，也就是说我们不需要任何实际的资源管理器对象。它的成员和函数应该是公开可用的(静态)
    ResourceManager() { }
    // 从文件加载并生成一个着色器
    static Shader    loadShaderFromFile(const char* vShaderFile, const char* fShaderFile, const char* gShaderFile = nullptr);
    // 从文件中加载单个纹理
    static Texture2D loadTextureFromFile(const char* file, bool alpha);
};

#endif