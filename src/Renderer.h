#ifndef RENDERER_H
#define RENDERER_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "texture.h"
#include "shader.h"
#include "mesh.h"


// 这是一个封装渲染代码的工具类
class Renderer
{
public:
    // 构造函数 (初始化模型、着色器、纹理)
    Renderer(Model& model, Shader &shader, Texture2D &texture);
    // 析构函数
    ~Renderer();
    // 绘制
    void setPbrShaderParameters(glm::vec3 albedo, float metallic, float roughness, float ao);
    void Draw(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 scale = glm::vec3(1.0f, 1.0f, 1.0f));
private:
    Model model;
    Shader shader;
    Texture2D texture;
    void initRenderData();

};

#endif

