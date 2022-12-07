#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include <map>
#include <string>

#include <glad/glad.h>

#include "shader.h"
#include "texture.h"

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
    // ���ļ��м�����ɫ��
    static Shader    LoadShader(const char* vShaderFile, const char* fShaderFile, const char* gShaderFile, std::string name);
    // ��������ȡ���Ѵ洢����ɫ��
    static Shader    GetShader(std::string name);
    // ���ļ��м�������
    static Texture2D LoadTexture(const char* file, bool alpha, std::string name);
    // ����һ���Ѵ洢������
    static Texture2D GetTexture(std::string name);
    // ��ȷ�ط��������Ѽ��ص���Դ
    static void      Clear();
private:
    // ˽�й��캯����Ҳ����˵���ǲ���Ҫ�κ�ʵ�ʵ���Դ�������������ĳ�Ա�ͺ���Ӧ���ǹ������õ�(��̬)
    ResourceManager() { }
    // ���ļ����ز�����һ����ɫ��
    static Shader    loadShaderFromFile(const char* vShaderFile, const char* fShaderFile, const char* gShaderFile = nullptr);
    // ���ļ��м��ص�������
    static Texture2D loadTextureFromFile(const char* file, bool alpha);
};

#endif