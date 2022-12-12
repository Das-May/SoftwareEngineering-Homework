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


// ��������
struct SceneParameter {
    float width, length;
    vector<float> obstacles_postion_x;
    vector<float> obstacles_postion_z;
};

// ��ɫ����
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

// ����ģʽ
// ���ز������������洢 ��ɫ��/����/ģ��
// ���еĹ��ܺ���Դ���Ǿ�̬��
// û�й��еĹ�����
class ResourceManager
{
public:
    // ��������Դ�洢���ֵ��У�����������
    static std::map<std::string, Shader>    Shaders;
    static std::map<std::string, Texture2D>    Textures;
    static std::map<std::string, Model>    Models;
    static string currentName;
    static Parameter Parameters;

    // ���ļ��м�����ɫ��
    static Shader& LoadShader(const char* vShaderFile, const char* fShaderFile, const char* gShaderFile, std::string name);
    // ��������ȡ���Ѵ洢����ɫ��
    static Shader& GetShader(std::string name);
    // ���ļ��м�������
    static Texture2D& LoadTexture(const char* file, bool alpha, std::string name);
    // ����һ���Ѵ洢������
    static Texture2D& GetTexture(std::string name);
    // ���ļ��м���ģ��
    static Model& LoadModel(string const& path, std::string name);
    // ����һ���Ѵ洢��ģ��
    static Model& GetModel(std::string name);
    // �����û�����
    static Parameter LoadParameter();
    // ��ȷ�ط��������Ѽ��ص���Դ
    static void      Clear();
private:
    // ˽�й��캯����Ҳ����˵���ǲ���Ҫ�κ�ʵ�ʵ���Դ�������������ĳ�Ա�ͺ���Ӧ���ǹ������õ�(��̬)
    ResourceManager() { }
    // ���ļ����ز�����һ����ɫ��
    static Shader    loadShaderFromFile(const char* vShaderFile, const char* fShaderFile, const char* gShaderFile = nullptr);
    // ���ļ��м��ص�������
    static Texture2D loadTextureFromFile(const char* file, bool alpha);
    // ���ļ��м��ؾ���֧�ֵ�ASSIMP��չ����ģ�ͣ������õ�������洢������������
    static void loadModel(string const& path);
    static void processNode(aiNode* node, const aiScene* scene);
    static Mesh processMesh(aiMesh* mesh, const aiScene* scene);

};

#endif