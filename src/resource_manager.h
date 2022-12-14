#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include <map>
#include <vector>
#include <string>

#include <glad/glad.h>

#include "shader.h"
#include "texture.h"
#include "mesh.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>


// 场景参数
struct SceneParameter {
    float width, length;
    vector<float> obstacles_postion_x;
    vector<float> obstacles_postion_z;
};

// 角色参数
struct CharacterParameter {
    float x, z, hp, atk;
    CharacterParameter(float x, float z, float hp, float atk):x(x),z(z),hp(hp),atk(atk){}
    CharacterParameter():x(x), z(z), hp(0), atk(0) {}
};

struct Parameter
{
    SceneParameter scene_parameter;
    CharacterParameter player_parameter;
    vector<CharacterParameter> enemy_parameter;
    vector<CharacterParameter> bag_parameter;

};

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
    static std::map<std::string, Model>    Models;
    static string currentName;
    static Parameter Parameters;

    // 从文件中加载着色器
    static Shader& LoadShader(const char* vShaderFile, const char* fShaderFile, const char* gShaderFile, std::string name);
    // 检索（获取）已存储的着色器
    static Shader& GetShader(std::string name);
    // 从文件中加载纹理
    static Texture2D& LoadTexture(const char* file, bool alpha, std::string name);
    // 检索一个已存储的纹理
    static Texture2D& GetTexture(std::string name);
    // 从文件中加载模型
    static Model& LoadModel(string const& path, std::string name);
    // 检索一个已存储的模型
    static Model& GetModel(std::string name);
    // 加载用户参数
    static Parameter LoadParameter();
    // 正确地分配所有已加载的资源
    static void      Clear();
private:
    // 私有构造函数，也就是说我们不需要任何实际的资源管理器对象。它的成员和函数应该是公开可用的(静态)
    ResourceManager() { }
    // 从文件加载并生成一个着色器
    static Shader    loadShaderFromFile(const char* vShaderFile, const char* fShaderFile, const char* gShaderFile = nullptr);
    // 从文件中加载单个纹理
    static Texture2D loadTextureFromFile(const char* file, bool alpha);
    // 从文件中加载具有支持的ASSIMP扩展名的模型，并将得到的网格存储在网格向量中
    static void loadModel(string const& path);
    static void processNode(aiNode* node, const aiScene* scene);
    static Mesh processMesh(aiMesh* mesh, const aiScene* scene);

};

#endif