#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include <map>
#include <string>

#include <glad/glad.h>

//#include "texture.h"
#include "shader.h"


// ����ģʽ
// ���ز������������洢 ��ɫ��/����/ģ��
// ���еĹ��ܺ���Դ���Ǿ�̬��
// û�й��еĹ�����
class ResourceManager
{
public:
    // ��������Դ�洢���ֵ��У�����������
    static std::map<std::string, Shader>    Shaders;
    // ���ļ��м�����ɫ��
    static Shader    LoadShader(const char* vShaderFile, const char* fShaderFile, const char* gShaderFile, std::string name);
    // ��������ȡ���Ѵ洢����ɫ��
    static Shader    GetShader(std::string name);
    static void      Clear();
private:
    // ˽�й��캯����Ҳ����˵���ǲ���Ҫ�κ�ʵ�ʵ���Դ�������������ĳ�Ա�ͺ���Ӧ���ǹ������õ�(��̬)
    ResourceManager() { }
    // ���ļ����ز�����һ����ɫ��
    static Shader    loadShaderFromFile(const char* vShaderFile, const char* fShaderFile, const char* gShaderFile = nullptr);
};

#endif