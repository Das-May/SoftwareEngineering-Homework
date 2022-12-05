#ifndef SHADER_H
#define SHADER_H

#include <string>

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>


// 通用着色器对象
// 生成编译/链接时间错误消息
// 托管几个实用函数，方便管理
class Shader
{
public:
    // state
    unsigned int ID;
    // 构造函数
    Shader() { }
    // 激活当前着色器
    Shader& Use();
    // 根据所给的着色器代码，编译着色器（顶点着色器、片元着色器、几何着色器）
    void    Compile(const char* vertexSource, const char* fragmentSource, const char* geometrySource = nullptr); // note: geometry source code is optional 
    // 实用函数
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
    // 检查编译或链接是否失败，如果失败，则打印错误日志
    void    checkCompileErrors(unsigned int object, std::string type);
};

#endif