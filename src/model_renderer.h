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
    // ���캯�� (inits shaders/shapes)
    ModelRenderer(string const& path, Shader shader);
    // ��������
    ~ModelRenderer();
    // ����transform��Ϣ����Ⱦģ�ͣ���ͼ��Model�Զ���ȡ��
    void DrawModel(glm::vec3 position, glm::vec3 scale = glm::vec3(1.0f), GLfloat rotate = 0.0f, glm::vec3 color = glm::vec3(1.0f));
private:
    // Render state
    Model model;
    Shader shader;
    // ��ʼ��һЩ����
    void initRenderData();
};


#endif

