//#pragma once
#ifndef MODEL_RENDERER_H
#define MODEL_RENDERER_H

#include <GL/glew.h>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "model.h"
#include "texture.h"
#include "shader.h"

#include <string>
using namespace std;

class ModelRenderer
{
public:
    // 构造函数 (inits shaders/shapes)
    ModelRenderer(string const& path, Shader shader);
    // 析构函数
    ~ModelRenderer();
    // 根据transform信息，渲染模型（贴图由Model自动读取）
    void DrawModel(glm::vec3 position, glm::vec3 scale = glm::vec3(1.0f), GLfloat rotate = 0.0f, glm::vec3 color = glm::vec3(1.0f));
private:
    // Render state
    Model model;
    Shader shader;
    // 初始化一些数据
    void initRenderData();
};


#endif

