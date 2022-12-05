#ifndef SHADER_H
#define SHADER_H

#include <string>

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>


// ͨ����ɫ������
// ���ɱ���/����ʱ�������Ϣ
// �йܼ���ʵ�ú������������
class Shader
{
public:
    // state
    unsigned int ID;
    // ���캯��
    Shader() { }
    // ���ǰ��ɫ��
    Shader& Use();
    // ������������ɫ�����룬������ɫ����������ɫ����ƬԪ��ɫ����������ɫ����
    void    Compile(const char* vertexSource, const char* fragmentSource, const char* geometrySource = nullptr); // note: geometry source code is optional 
    // ʵ�ú���
    void    SetFloat(const char* name, float value, bool useShader = false);
    void    SetInteger(const char* name, int value, bool useShader = false);
    void    SetVector2f(const char* name, float x, float y, bool useShader = false);
    void    SetVector2f(const char* name, const glm::vec2& value, bool useShader = false);
    void    SetVector3f(const char* name, float x, float y, float z, bool useShader = false);
    void    SetVector3f(const char* name, const glm::vec3& value, bool useShader = false);
    void    SetVector4f(const char* name, float x, float y, float z, float w, bool useShader = false);
    void    SetVector4f(const char* name, const glm::vec4& value, bool useShader = false);
    void    SetMatrix4(const char* name, const glm::mat4& matrix, bool useShader = false);
private:
    // ������������Ƿ�ʧ�ܣ����ʧ�ܣ����ӡ������־
    void    checkCompileErrors(unsigned int object, std::string type);
};

#endif